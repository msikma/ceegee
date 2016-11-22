/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/usp_talon.h"

DATAFILE *USP_TALON_DAT;
int USP_TALON_LOADED = FALSE;

/**
 * Load the test sprite into memory.
 */
int load_usp_talon_dat() {
    if (USP_TALON_LOADED == TRUE) {
        return 0;
    }
    USP_TALON_DAT = load_datafile(USP_TALON_PATH);

    if (!USP_TALON_DAT) {
        return 1;
    }

    USP_TALON_LOADED = TRUE;
    return 0;
}

/**
 * Unload the test sprite.
 */
void unload_usp_talon_dat() {
    unload_datafile(USP_TALON_DAT);
    USP_TALON_LOADED = FALSE;
}
