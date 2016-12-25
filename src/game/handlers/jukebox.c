/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/game/loop/state.h"
#include "src/gfx/modes.h"
#include "src/gfx/bitmaps.h"

/**
 * Request the jukebox handler dependencies.
 */
void jukebox_deps() {
}

/**
 * Initialize the jukebox handler.
 *
 * This handler is used when the game boots up. It sets up whatever
 * needs to be done for the game globally and then hands over control
 * to the next handler.
 */
void jukebox_init() {
}

/**
 * Update the internal state of the jukebox handler.
 */
void jukebox_update() {
}

/**
 * Renders the output of the jukebox handler's current game state.
 */
void jukebox_render(BITMAP *buffer) {
}

/**
 * Whether or not the jukebox handler will shutdown and exit.
 */
bool jukebox_will_exit() {
    return true;
}

/**
 * Shutdown and exit the jukebox handler.
 */
void jukebox_exit() {
    set_next_state(STATE_EXIT);
}
