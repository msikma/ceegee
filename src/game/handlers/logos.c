/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>

#include "src/audio/midi.h"
#include "src/game/state.h"
#include "src/gfx/bitmaps.h"
#include "src/gfx/res/flim.h"
#include "src/gfx/res/tin.h"
#include "src/gfx/res/logos.h"
#include "src/gfx/text.h"
#include "src/utils/version.h"

// Fade speed. The speed goes from 1 (the slowest) up to 64 (instantaneous).
const int FADE_SPEED = 5;

/**
 * Shows the logos used during the startup sequence, e.g. publisher and title.
 */
static void show_startup_logos() {
    load_logos_dat();
    load_flim_dat();
    load_tin_dat();
}

/**
 * Initialize the logos handler.
 *
 * Used to display the logos at the start of the game. A series of logos
 * are displayed which fade in and then wait for the user to press any key.
 * Once the user presses a key, the next logo is shown. When all logos are
 * shown, the handler exits.
 */
void logos_init() {
    // Play music, display logos and then shut down.
    music_start(&MUSIC_LOGOS);
    show_startup_logos();
}

/**
 * Update the internal state of the logos handler.
 *
 * Nothing happens here because there's no need to respond to any
 * user input.
 */
void logos_update() {
}

/**
 * Renders the output of the logos handler's current game state.
 *
 * The drawing routines are all blocking, meaning one "frame" is enough
 * to fade all logos in and out.
 */
void logos_render(BITMAP *buffer) {
    // We're going to draw text on top of the image,
    // so add the text palette to the image.
    add_flim_palette_colors(LOGOS_DAT[ASLOGO_PALETTE].dat);

    // Display the main logo with text drawn on top.
    set_palette(black_palette);
    blit(LOGOS_DAT[ASLOGO_IMG].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    draw_text(screen, 160, 154, TXT_WHITE, -1, -1,
        TXT_REGULAR, TXT_CENTER, "(C) 2016, Avalanche Studios");
    draw_text(screen, 160, 154 + FLIM_HEIGHT + 2, TXT_WHITE, -1, -1,
        TXT_REGULAR, TXT_CENTER, "www.avalanchestudios.net");
    if (DEBUG) {
        draw_text(screen, 160, 154 + FLIM_HEIGHT + 18, TXT_GRAY, -1, -1,
            TXT_SMALL, TXT_CENTER, (char *)get_short_version());
    }
    fade_from(black_palette, LOGOS_DAT[ASLOGO_PALETTE].dat, FADE_SPEED);

    // Wait for any key, then draw the second logo.
    readkey();
    fade_out(FADE_SPEED);
    set_palette(black_palette);
    blit(LOGOS_DAT[TEST_IMG].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    fade_from(black_palette, LOGOS_DAT[TEST_PALETTE].dat, FADE_SPEED);

    // Wait for any key, then finish. This handler immediately exits
    // after running the logos_render() function once, so this code
    // is guaranteed to only run once.
    readkey();
    fade_out(FADE_SPEED);
}

/**
 * Whether or not the logos handler will shutdown and exit.
 *
 * Since all rendering we do is blocking, we can immediately exit
 * after doing a single logos_render() call, which is guaranteed
 * to happen at least once.
 */
bool logos_will_exit() {
    return true;
}

/**
 * Shutdown and exit the logos handler.
 */
void logos_exit() {
    music_stop();
    unload_logos_dat();
    set_next_state(STATE_FLYING);
}
