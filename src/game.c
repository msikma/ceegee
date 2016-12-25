/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/game.h"
#include "src/game/loop/loop.h"
#include "src/game/loop/state.h"
#include "src/game/state.h"
#include "src/gfx/deps/manager.h"
#include "src/gfx/deps/register.h"
#include "src/gfx/modes.h"

/**
 * Starts the game after the main program is executed.
 *
 * This initializes Allegro, then hands over control to the game loop.
 */
void start_game() {
    initialize_resources();
    game_state.loop_state_post_init = STATE_LOGOS;
    game_loop();
}

/**
 * Starts the application with the jukebox as the first state.
 */
void start_jukeboxa() {
    initialize_resources();
    game_state.loop_state_post_init = STATE_JUKEBOX;
    game_loop();
}

/**
 * Performs all initialization that must occur regardless of which
 * initial state we're using.
 */
void initialize_resources() {
    // Install Allegro drivers.
    initialize_allegro();
    // Register our game resources to the dependency manager.
    register_resources();
    // Set up the game state defaults.
    initialize_game_state();
}

/**
 * Returns to text mode and prints a thank you note.
 * Called just before program shutdown.
 */
void shutdown() {
    set_palette(black_palette);
    clear_bitmap(screen);
    screen_text_mode();
    printf("Thanks for playing Ceegee.\r\n");

    // Print out the resource list if debugging.
    if (DEBUG) {
        debug_res_list();
    }
}
