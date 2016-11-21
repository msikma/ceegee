/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/tin.h"

DATAFILE *TIN_DAT;
int TIN_HEIGHT;
int TIN_LOADED = FALSE;

/**
 * Adds the Tin font standard colors to a palette.
 * The colors are added at the end of the palette.
 */
void add_tin_palette_colors(RGB *pal) {
    pal[254].r = pal[254].g = pal[254].b = 63;
    pal[253].r = pal[253].g = pal[253].b = 28;
    pal[252].r = pal[252].g = pal[252].b = 12;
}

/**
 * Load the Tin font into memory.
 */
int load_tin_dat() {
    if (TIN_LOADED == TRUE) {
        return 0;
    }
    TIN_DAT = load_datafile(TIN_PATH);

    if (!TIN_DAT) {
        return 1;
    }

    // Acquire the font height, slightly adjusted.
    TIN_HEIGHT = text_height(TIN_DAT[TIN_WHITE].dat) - 4;

    TIN_LOADED = TRUE;
    return 0;
}

/**
 * Unload the Tin font. Unnecessary since it's used everywhere
 * in the game.
 */
void unload_tin_dat() {
    unload_datafile(TIN_DAT);
}
