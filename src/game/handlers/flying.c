/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>

#include "src/game/handlers/flying.h"
#include "src/game/state.h"
#include "src/gfx/res/flim.h"
#include "src/gfx/modes.h"
#include "src/gfx/text.h"

//test
#include "src/gfx/res/usp_talon.h"
#include "src/audio/midi.h"

int sx;
int sy;
int sw = 50;
int sh = 50;

/**
 * Request the flying handler dependencies.
 */
void flying_deps() {
}

/**
 * Initialize the flying handler.
 */
void flying_init() {
    load_usp_talon_dat();
    add_flim_palette_colors(USP_TALON_DAT[USP_TALON_PALETTE].dat);
    set_palette(USP_TALON_DAT[USP_TALON_PALETTE].dat);

    COMPILED_SPRITE *usptalon = (COMPILED_SPRITE *)USP_TALON_DAT[USP_TALON_M].dat;

    sx = 150;
    sy = 80;
    sw = usptalon->w;
    sh = usptalon->h;
}

/**
 * Update the internal state of the flying handler.
 *
 * Polls the keyboard and then calculates the appropriate effect
 * on the game state.
 */
void flying_update() {
    poll_keyboard();

    if (key[KEY_LEFT]) {
        sx -= 2;
    }
    if (key[KEY_RIGHT]) {
        sx += 2;
    }
    if (key[KEY_UP]) {
        sy -= 2;
    }
    if (key[KEY_DOWN]) {
        sy += 2;
    }

    if (sx < 0) {
        sx = 0;
    }
    if (sy < 0) {
        sy = 0;
    }
    if (sx > CEEGEE_SCR_W - sw) {
        sx = CEEGEE_SCR_W - sw;
    }
    if (sy > CEEGEE_SCR_H - sh) {
        sy = CEEGEE_SCR_H - sh;
    }
}

/**
 * Renders the output of the flying handler's current game state.
 */
void flying_render(BITMAP *buffer) {
    clear_to_color(buffer, palette_color[252]);
    draw_compiled_sprite(buffer, USP_TALON_DAT[USP_TALON_M].dat, sx, sy);

    if (DEBUG) {
        draw_textf(buffer, 0, 0, TXT_WHITE, -1, -1, TXT_REGULAR, TXT_LEFT,
            "x: %03d, y: %03d, w: %03d, h: %03d", sx, sy, sw, sh);
    }
}

/**
 * Whether or not the flying handler will shutdown and exit.
 */
bool flying_will_exit() {
    if (key[KEY_ESC]) {
        return true;
    }
    return false;
}

/**
 * Shutdown and exit the flying handler.
 */
void flying_exit() {
    // Shut down the game after this handler is complete.
    set_next_state(STATE_EXIT);
}
