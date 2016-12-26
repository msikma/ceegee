/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/game/loop/state.h"
#include "src/game/state.h"
#include "src/gfx/bitmaps.h"
#include "src/gfx/modes.h"

/**
 * Request the initial handler dependencies.
 */
void initial_deps() {
}

/**
 * Initialize the initial handler.
 *
 * This handler is used when the game boots up. It sets up whatever
 * needs to be done for the game globally and then hands over control
 * to the next handler.
 */
void initial_init() {
    // Try to change to graphics mode.
    if (screen_gfx_mode() != 0) {
        printf("Cannot initialize Ceegee:\r\n%s\r\n", allegro_error);
        return;
    }
}

/**
 * Update the internal state of the initial handler.
 */
void initial_update() {
}

/**
 * Renders the output of the initial handler's current game state.
 */
void initial_render(BITMAP *buffer) {
}

/**
 * Whether or not the initial handler will shutdown and exit.
 */
bool initial_will_exit() {
    return true;
}

/**
 * Shutdown and exit the initial handler.
 */
void initial_exit() {
    set_next_state(game_state.loop_state_post_init);
}
