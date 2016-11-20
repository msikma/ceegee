/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/game/loop.h"
#include "src/gfx/modes.h"

/**
 * Starts the game after the main program is executed.
 *
 * This initializes Allegro, then starts the game loop.
 */
void start_game() {
    // Install Allegro drivers and hand over control to the game loop.
    initialize_allegro();
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
}
