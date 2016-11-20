/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/audio/midi.h"
#include "src/game.h"
#include "src/game/loop.h"
#include "src/gfx/bitmaps.h"

// Whether Allegro is initialized.
int ALLEGRO_INITIALIZED = FALSE;

/**
 * Starts the game after the main program is executed.
 *
 * This initializes Allegro, then sets the appropriate video mode and
 * begins displaying our logos. Currently nothing else happens.
 *
 * Returns 1 if no appropriate graphics mode could be set, 0 otherwise.
 */
int start_game() {
    // Install Allegro drivers.
    initialize();

    // Try to change to graphics mode.
    if (screen_gfx_mode() != 0) {
        printf("Cannot initialize Allegro:\r\n%s\r\n", allegro_error);
        return 1;
    }

    // Play music, display logos and then shut down.
    music_start(&MUSIC_LOGOS);
    show_startup_logos();
    game_loop();
    return 0;
}

/**
 * Starts up Allegro and installs its drivers. Used once at the start.
 * Accidental double initializations are prevented. If we can't initialize
 * for any reason, 1 is returned, otherwise 0.
 */
int initialize() {
    if (ALLEGRO_INITIALIZED == TRUE) {
        return 0;
    }
    if (allegro_init() != 0) {
        return 1;
    }

    install_timer();
    install_keyboard();
    set_color_conversion(COLORCONV_NONE);

    ALLEGRO_INITIALIZED = TRUE;

    return 0;
}

/**
 * Sets the standard graphics mode, which is 320x200@8bpp.
 * Returns 1 if the mode can't be set for some reason, 0 otherwise.
 */
int screen_gfx_mode() {
    set_color_depth(8);
    if (set_gfx_mode(GFX_AUTODETECT, CEEGEE_SCR_W, CEEGEE_SCR_H, 0, 0) != 0) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Cannot set graphics mode:\r\n%s\r\n", allegro_error);
        return 1;
    }
    return 0;
}

/**
 * Returns us to text mode. Always expected to be possible, so it
 * always returns 0.
 */
int screen_text_mode() {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return 0;
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
