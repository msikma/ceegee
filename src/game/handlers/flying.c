/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>

#include "src/game/handlers/flying.h"
#include "src/game/state.h"

//test
#include "src/gfx/res/usp_talon.h"
#include "src/audio/midi.h"

int sx;
int sy;

/**
 * Initialize the flying handler.
 */
void flying_init() {
    load_usp_talon_dat();
    set_palette(black_palette);
    sx = 150;
    sy = 80;
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
        sx -= 1;
    }
    if (key[KEY_RIGHT]) {
        sx += 1;
    }
    if (key[KEY_UP]) {
        sy -= 1;
    }
    if (key[KEY_DOWN]) {
        sy += 1;
    }
}

/**
 * Renders the output of the flying handler's current game state.
 */
void flying_render(BITMAP *buffer) {
    clear_to_color(buffer, palette_color[255]);
    draw_compiled_sprite(buffer, USP_TALON_DAT[USP_TALON_M].dat, sx, sy);
    set_palette(USP_TALON_DAT[USP_TALON_PALETTE].dat);
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
