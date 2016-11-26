/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/game/handlers/flying.h"
#include "src/game/state.h"
#include "src/gfx/res/flim.h"
#include "src/gfx/modes.h"
#include "src/gfx/text.h"

//test
#include "src/gfx/res/usp_talon.h"
#include "src/game/sprites/ships.h"

SHIP theship;

/**
 * Request the flying handler dependencies.
 */
void flying_deps() {
    load_flim_dat();
    load_usp_talon_dat();
}

/**
 * Initialize the flying handler.
 */
void flying_init() {
    add_flim_palette_colors(USP_TALON_DAT[USP_TALON_PALETTE].dat);
    set_palette(USP_TALON_DAT[USP_TALON_PALETTE].dat);

    theship = ship_create(USP_TALON);
    ship_set_pos(&theship, 150, 80);
}

/**
 * Update the internal state of the flying handler.
 *
 * Polls the keyboard and then calculates the appropriate effect
 * on the game state.
 */
void flying_update() {
    poll_keyboard();
    ship_feed_input(&theship);
}

/**
 * Renders the output of the flying handler's current game state.
 */
void flying_render(BITMAP *buffer) {
    clear_to_color(buffer, palette_color[252]);
    ship_draw(&theship, buffer);

    if (DEBUG) {
        draw_textf(buffer, 0, 0, TXT_WHITE, -1, -1, TXT_REGULAR, TXT_LEFT,
            "x: %03d, y: %03d, w: %03d, h: %03d, pivot: %03d",
            theship.x, theship.y, theship.w, theship.h, theship.pivot);
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
