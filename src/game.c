/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "game.h"
#include "midi.h"

// Whether Allegro is initialized.
int ALLEGRO_INITIALIZED = 0;

/**
 * Runs the game itself. At the moment it just shows a "hello world" though.
 * Returns status code.
 */
int start_game() {
    initialize();

    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Cannot set graphics mode:\r\n%s\r\n", allegro_error);
        return 1;
    }

    // Print a single line of "hello world" on a white screen.
    set_palette(desktop_palette);
    clear_to_color(screen, makecol(255, 255, 255));
    textout_centre_ex(screen, font, "Hello, world!", SCREEN_W / 2, SCREEN_H / 2, makecol(0,0,0), -1);

    // Play music, then exit after a keypress.
    music_start("music\\wit2.mid");
    readkey();
    music_stop();
    shutdown();
    return 0;
}

/**
 * Starts up Allegro. Used once at the start of the program.
 * Prevents accidental double initializations.
 */
int initialize() {
    if (ALLEGRO_INITIALIZED == 1) {
        return 0;
    }
    if (allegro_init() != 0) {
        printf("Cannot initialize Allegro:\r\n%s\r\n", allegro_error);
        return 1;
    }

    install_timer();
    install_keyboard();

    ALLEGRO_INITIALIZED = 1;
}

/**
 * Called just before program shutdown.
 */
void shutdown() {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    printf("Thanks for playing Ceegee.\r\n");
}
