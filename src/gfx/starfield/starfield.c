/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <xorshift.h>
#include <stdbool.h>

#include "src/game.h"
#include "src/gfx/starfield/algos.h"
#include "src/gfx/starfield/starfield.h"

// Number of hue shades.
const int SHADES = 17;
// Offset at which the color shades begin.
const int SHADES_OFFSET = 1;
// Number of luminance variants per shade.
const float LUMS[] = { 1.0, 0.5, 0.25 };
const int LUM_N = sizeof(LUMS) / sizeof(float);

// Maximum rendering coordinates, and centers, for our stars.
const int STAR_X_LIM = CEEGEE_SCR_W - (((sizeof(LUMS) / sizeof(float)) * 2) - 1);
const int STAR_Y_LIM = CEEGEE_SCR_H - (((sizeof(LUMS) / sizeof(float)) * 2) - 1);
const int STAR_X_C = (CEEGEE_SCR_W - (((sizeof(LUMS) / sizeof(float)) * 2) - 1)) / 2;
const int STAR_Y_C = (CEEGEE_SCR_H - (((sizeof(LUMS) / sizeof(float)) * 2) - 1)) / 2;

// Star definition. Contains a set of coordinates and a color value.
// x, y and z are used to determine a star's base position.
// n is a number from 0 to STAR_MULTIPLIER.
// xpos, ypos are where they appear on screen after distance calculation.
// c is the palette value the star will use when rendered.
// vis determines whether the star is visible or not.
typedef struct star {
   float x, y;
   int z, n, xpos, ypos, c;
   bool vis;
} star;

// Number of visible stars. Must be a multiple of STAR_MAX_DIST.
const int STAR_AMOUNT = 1152;
// Must be STAR_AMOUNT / STAR_MAX_DIST.
const int STAR_MULTIPLIER = 8;
// The maximum distance (the point where the last color shade is shown).
const int STAR_MAX_DIST = 144;
// Speed at which the stars move, per vblank.
const int STAR_SPEED = 1;
// Speeds up the stars closer by the user. Turn off when making new algorithms.
const int STAR_WARP_SPEED = TRUE;

// The visible universe.
star starfield[1152];
// Whether the starfield has been initialized.
bool starfield_initialized = FALSE;
// Counter used to determine rendering algorithm.
int counter = 0;
// Current rendering algorithm.
int render_algo = 0;

/**
 * Draws a single star at x and y, using the LUM_N colors from offset c.
 * The color offset must be the first of the set.
 *
 * Uses _putpixel(), so use with care. Don't call with invalid x/y values.
 */
void draw_star(BITMAP *buffer, int x, int y, int c) {
    int a, b;
    int center = LUM_N - 1;

    // Center dot.
    _putpixel(buffer, center + x, center + y, palette_color[c]);

    // All other shades.
    for (a = 1; a < LUM_N; ++a) {
        _putpixel(buffer, center + x, center - a + y, palette_color[c + a]);
        _putpixel(buffer, center + x, center + a + y, palette_color[c + a]);
        _putpixel(buffer, center - a + x, center + y, palette_color[c + a]);
        _putpixel(buffer, center + a + x, center + y, palette_color[c + a]);
    }
}

/**
 * Returns the proper first color color index for a shade of hue.
 */
int star_hue_color(int hue) {
    return SHADES_OFFSET + (hue * 3);
}

/**
 * Updates the rendering algorithm counter.
 */
void update_starfield_counter() {
    ++counter;
}

/**
 * Updates the starfield; runs once per frame.
 *
 * This performs any update logic that needs to occur and then draws
 * all stars.
 */
void update_starfield(BITMAP *buffer) {
    set_star_pos_algo();
    move_starfield();
    draw_starfield(buffer);
}

/**
 * Sets the correct star positioning algorithm for this frame.
 *
 * To render the stars, we use one of a number of algorithms to determine
 * each individual star's initial x and y coordinates. We regularly switch
 * algorithms to show different visual effects. This function sets the
 * pointer to the algorithm function, switching once every COUNTER_MAX frames.
 */
void set_star_pos_algo() {
    // Starting algorithm.
    if (star_algo_ptr == 0) {
        star_algo_ptr = ALGORITHMS[render_algo];
    }

    if (counter > COUNTER_MAX) {
        // Counter is full, so go to the next algorithm and reset the counter.
        counter = 0;
        if (++render_algo >= ALGOS) {
            render_algo = 0;
        }
        star_algo_ptr = ALGORITHMS[render_algo];
    }
}

/**
 * Sets the initial positions of each individual star.
 * This function should only run once at the start.
 */
void initialize_star_positions() {
    int a;
    float progress = (float)counter / COUNTER_MAX;

    if (starfield_initialized) {
        return;
    }

    // Run through all stars and set them to an initial position.
    // The z position is especially important. It's set only once
    // and is never changed, to ensure we have an even number
    // of stars across the entire visible distance.
    for (a = 0; a < STAR_AMOUNT; ++a) {
        starfield[a].n = a / STAR_MAX_DIST;
        starfield[a].z = (a % STAR_MAX_DIST) + 1;
        starfield[a].vis = TRUE;
        star_algo_ptr(
            &starfield[a].x, &starfield[a].y, &starfield[a].n,
            counter, COUNTER_MAX, progress
        );
    }
    starfield_initialized = TRUE;
}

/**
 * Determines the positions and colors of the stars.
 *
 * Stars can be either in a visible or invisible state. If visible, we
 * determine the next set of coordinates and render the star. If invisible,
 * we reset the star to a starting position somewhere in the center.
 */
void move_starfield() {
    int a, sx, sy, sc;
    star *star;
    float hue;
    float progress = (float)counter / COUNTER_MAX;

    for (a = 0; a < STAR_AMOUNT; ++a) {
        star = &starfield[a];

        // Move the star towards the viewer.
        (*star).z -= STAR_SPEED;
        // Extra speed boost when they're close by.
        if (STAR_WARP_SPEED == TRUE && starfield[a].z < 96) {
            (*star).z -= STAR_SPEED;
        }

        // Reset the star back to the starting position if it's too close.
        if ((*star).z < 1) {
            star_algo_ptr(
                &(*star).x, &(*star).y, &(*star).n,
                counter, COUNTER_MAX, progress
            );
            (*star).z = STAR_MAX_DIST;
            (*star).vis = TRUE;
        }
        sx = (((*star).x * STAR_X_LIM) / ((*star).z - (*star).n) + (STAR_X_C));
        sy = (((*star).y * STAR_Y_LIM) / ((*star).z - (*star).n) + (STAR_Y_C));

        // If the star is out of bounds, don't draw it.
        if (sx < 0 || sx > STAR_X_LIM || sy < 0 || sy > STAR_Y_LIM) {
            (*star).vis = FALSE;
            continue;
        }

        // The hue selection contains some fine-tuning to ensure there's
        // always a bit of red close by, and pink in the far distance.
        hue = (((float)(*star).z - 50) / (STAR_MAX_DIST - 38));
        hue = hue < 1.0 ? hue : 1.0;
        hue = hue > 0.0 ? hue : 0.0;
        sc = star_hue_color(ceil(hue * (SHADES - 1)));

        (*star).xpos = sx;
        (*star).ypos = sy;
        (*star).c = sc;
    }
}

/**
 * Draws all currently visible stars onto the buffer.
 */
void draw_starfield(BITMAP *buffer) {
    for (int a = 0; a < STAR_AMOUNT; ++a) {
        if (starfield[a].vis == FALSE) {
            continue;
        }
        draw_star(buffer, starfield[a].xpos, starfield[a].ypos, starfield[a].c);
    }
}

/**
 * Initialization routine.
 *
 * Sets all stars to the starting position. Their initial coordinates
 * are determined in the main loop. Also installs the algorithm timer.
 */
void initialize_starfield() {
    for (int a = 0; a < STAR_AMOUNT; ++a) {
        starfield[a].z = 0;
    }
    // Install algorithm selection timer.
    install_int_ex(update_starfield_counter, BPS_TO_TIMER(60));
    // Set up the initial star positions.
    set_star_pos_algo();
    initialize_star_positions();
}

/**
 * Returns the palette used for the starfield.
 *
 * The colors are generated by picking SHADES number of hues
 * and adding LUM_N number of variants of that hue to the palette.
 */
RGB *get_starfield_palette() {
    int a, sha, lum, r, g, b, offset;
    RGB *pal;

    pal = malloc(sizeof(PALETTE));

    // Set all skipped colors to black.
    for (a = 0; a < SHADES_OFFSET; ++a) {
        pal[a].r = pal[a].g = pal[a].b = 0;
    }

    // Add several color swatches and their darker variants.
    for (sha = 0; sha < SHADES; ++sha) {
        offset = (sha * LUM_N) + SHADES_OFFSET;
        for (lum = 0; lum < LUM_N; ++lum) {
            hsv_to_rgb((COUNTER_MAX / SHADES) * sha, 1, LUMS[lum], &r, &g, &b);
            pal[offset + lum].r = r / 4;
            pal[offset + lum].g = g / 4;
            pal[offset + lum].b = b / 4;
        }
    }

    // Fill the rest of the palette with white.
    for (a = SHADES_OFFSET + (SHADES * LUM_N); a < PAL_SIZE; ++a) {
        pal[a].r = 63;
        pal[a].g = 63;
        pal[a].b = 63;
    }

    return pal;
}
