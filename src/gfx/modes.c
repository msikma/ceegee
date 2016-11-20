/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

#include "src/gfx/modes.h"

/**
 * Starts up Allegro and installs its drivers. Used once at the start.
 * If we can't initialize for any reason, 1 is returned, otherwise 0.
 */
int initialize_allegro() {
    if (allegro_init() != 0) {
        return 1;
    }

    install_timer();
    install_keyboard();
    set_color_conversion(COLORCONV_NONE);

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
