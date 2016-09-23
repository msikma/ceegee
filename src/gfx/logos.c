/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/logos.h"

// List of the logos we display on launch.
const char *LOGOS[] = {
    "data\\gfx\\title\\aslogo.pcx",
    "data\\gfx\\title\\test.pcx",
    0
};

/**
 * Shows the logos used during the startup sequence, e.g. publisher and title.
 */
void show_startup_logos() {
    show_logos(LOGOS);
}

/**
 * Displays an array of a logos.
 */
void show_logos(int *logos) {
    for (int a = 0; logos[a] != 0; ++a) {
        fade_in_bitmap(logos[a]);
        readkey();
        fade_out_bitmap();
    }
}

/**
 * Displays and fades in a single bitmap.
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
