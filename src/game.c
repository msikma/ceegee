/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "game.h"

/**
 * Runs the game itself. At the moment it just shows a "hello world" though.
 * Returns status code.
 */
int start_game() {
    // Initializes the Allegro library.
    if (allegro_init() != 0) {
        return 1;
    }

    // Installs the Allegro keyboard interrupt handler.
    install_keyboard();

    // Switch to graphics mode, 320x200.
    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Cannot set graphics mode:\r\n%s\r\n", allegro_error);
        return 1;
    }

    // Print a single line of "hello world" on a white screen.
    set_palette(desktop_palette);
    clear_to_color(screen, makecol(255, 255, 255));
    textout_centre_ex(screen, font, "Hello, world!", SCREEN_W / 2, SCREEN_H / 2, makecol(0,0,0), -1);

    // Wait for a keypress, then finish the program.
    readkey();
    shutdown();
    return 0;
}

/**
 * Called just before program shutdown.
 */
void shutdown() {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    printf("Thanks for playing Ceegee.\r\n");
}