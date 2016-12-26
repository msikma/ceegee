/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Displays and fades in a bitmap from a datafile.
 */
void fade_in_bitmap(BITMAP *image, RGB *pal, bool unload) {
    set_palette(black_palette);
    blit(image, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    fade_from(black_palette, pal, 5);

    // If desired, we'll unload the bitmap after using it.
    // This is only done for images that don't come from a datafile.
    if (unload) {
        destroy_bitmap(image);
    }
}

/**
 * Displays and fades in a single bitmap by filename.
 */
void fade_in_bitmap_file(char *file) {
    BITMAP *image;
    PALETTE pal;

    image = load_bitmap(file, pal);
    fade_in_bitmap(image, pal, TRUE);
}

/**
 * Fades out the current bitmap.
 */
void fade_out_bitmap() {
    fade_out(5);
}
