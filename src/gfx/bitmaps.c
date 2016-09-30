/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/bitmaps.h"
#include "src/gfx/res/logos.h"

/**
 * Shows the logos used during the startup sequence, e.g. publisher and title.
 */
void show_startup_logos() {
    load_logos_dat();

    for (int a = 0; a < 2; ++a) {
        fade_in_data_bmp(
            LOGOS[STARTUP_LOGO_BMP[a]].dat,
            LOGOS[STARTUP_LOGO_PAL[a]].dat
        );
        readkey();
        fade_out_bitmap();
    }
}

/**
 * Displays and fades in a bitmap from a datafile.
 */
void fade_in_data_bmp(BITMAP *image, RGB *pal) {
    set_palette(black_palette);
    blit(image, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    fade_from(black_palette, pal, 5);
    destroy_bitmap(image);
}

/**
 * Displays and fades in a single bitmap by filename.
 */
void fade_in_bitmap(char *file) {
    BITMAP *image;
    PALETTE pal;

    image = load_bitmap(file, pal);
    set_palette(black_palette);
    blit(image, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    fade_from(black_palette, pal, 5);
    destroy_bitmap(image);
}

/**
 * Fades out the current bitmap.
 */
void fade_out_bitmap() {
    fade_out(5);
}
