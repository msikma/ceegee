/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>

#include "src/game/handlers/flying.h"
#include "src/game/state.h"

//test
#include "src/gfx/res/logos.h"
#include "src/gfx/res/test_sprite.h"
#include "src/audio/midi.h"

int sx;
int sy;

/**
 * Initialize the flying handler.
 */
void flying_init() {
    load_logos_dat();
    load_test_sprite_dat();
    set_palette(black_palette);
    sx = 50;
    sy = 50;
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
    blit(LOGOS_DAT[STARTUP_LOGO_BMP[0]].dat, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    draw_compiled_sprite(buffer, TEST_SPRITE_DAT[TEST_SPRITE].dat, sx, sy);
    set_palette(LOGOS_DAT[STARTUP_LOGO_PAL[0]].dat);
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
