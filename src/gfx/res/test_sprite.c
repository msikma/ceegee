/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/test_sprite.h"

DATAFILE *TEST_SPRITE_DAT;
int TEST_SPRITE_LOADED = FALSE;

/**
 * Load the test sprite into memory.
 */
int load_test_sprite_dat() {
    if (TEST_SPRITE_LOADED == TRUE) {
        return 0;
    }
    TEST_SPRITE_DAT = load_datafile(TEST_SPRITE_PATH);

    if (!TEST_SPRITE_DAT) {
        return 1;
    }

    TEST_SPRITE_LOADED = TRUE;
    return 0;
}

/**
 * Unload the test sprite.
 */
void unload_test_sprite_dat() {
    unload_datafile(TEST_SPRITE_DAT);
    TEST_SPRITE_LOADED = FALSE;
}
