/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "flim.h"

DATAFILE *FLIM;
int FLIM_HEIGHT;
int FLIM_LOADED = FALSE;

/**
 * Adds the Flim font standard colors to a palette.
 * The colors are added at the end of the palette.
 */
void add_flim_palette_colors(RGB *pal) {
    pal[254].r = pal[254].g = pal[254].b = 63;
    pal[253].r = pal[253].g = pal[253].b = 28;
    pal[252].r = pal[252].g = pal[252].b = 12;
}

/**
 * Load the Flim font into memory.
 */
int load_flim() {
    if (FLIM_LOADED == TRUE) {
        return 0;
    }
    FLIM = load_datafile("data\\font\\flim.dat");

    if (!FLIM) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Error loading the Flim font.");
        return 1;
    }

    // Acquire the font height, slightly adjusted.
    FLIM_HEIGHT = text_height(FLIM[FLIM_WHITE].dat) - 4;

    FLIM_LOADED = TRUE;
    return 0;
}

/**
 * Unload the Flim font. Unnecessary since it's used everywhere
 * in the game.
 */
int unload_flim() {
    unload_datafile(FLIM);
}
