/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/game/loop.h"
#include "src/gfx/deps/manager.h"
#include "src/gfx/deps/register.h"
#include "src/gfx/modes.h"

/**
 * Starts the game after the main program is executed.
 *
 * This initializes Allegro, then starts the game loop.
 */
void start_game() {
    // Install Allegro drivers.
    initialize_allegro();
    // Register our game resources to the dependency manager.
    register_resources();
    // Hand over control to the game loop.
    game_loop();
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
