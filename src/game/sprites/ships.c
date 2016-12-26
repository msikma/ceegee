/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>

#include "src/game/sprites/ships.h"
#include "src/gfx/res/usp_talon.h"
#include "src/gfx/modes.h"

int scr_boundary_x = CEEGEE_SCR_W;
int scr_boundary_y = CEEGEE_SCR_H;

/**
 * Creates and returns a new ship instance.
 *
 * Requires a reference to a datafile for initializing the ship's graphics.
 */
SHIP ship_create(int type, DATAFILE* ship_data) {
    SHIP inst;
    switch (type) {
        case USP_TALON:
        default:
            inst.x = 0;
            inst.y = 0;
            inst.pivot = PIVOT_CENTER;
            inst.cspr_m = (COMPILED_SPRITE *)ship_data[USP_TALON_M].dat;
            inst.cspr_l1 = (COMPILED_SPRITE *)ship_data[USP_TALON_L1].dat;
            inst.cspr_l2 = (COMPILED_SPRITE *)ship_data[USP_TALON_L2].dat;
            inst.cspr_r1 = (COMPILED_SPRITE *)ship_data[USP_TALON_R1].dat;
            inst.cspr_r2 = (COMPILED_SPRITE *)ship_data[USP_TALON_R2].dat;
            inst.curr_frame = &inst.cspr_m;
            inst.w = inst.cspr_m->w;
            inst.h = inst.cspr_m->h;
            return inst;
    }
}

/**
 * Sets the ship's x and y positions directly. Useful when initializing.
 */
void ship_set_pos(SHIP *ship, int x, int y) {
    ship->x = x;
    ship->y = y;
}

/**
 * Draws a ship onto a buffer.
 */
void ship_draw(SHIP *ship, BITMAP *buffer) {
    draw_compiled_sprite(buffer, *ship->curr_frame, ship->x, ship->y);
}

/**
 * Feeds the current keyboard state to the ship, altering its appearance.
 * If the user has the left arrow key depressed, for example, the ship will
 * move left, and depending on its speed we might see a different sprite too.
 */
void ship_feed_input(SHIP *ship) {
    if (key[KEY_LEFT]) {
        ship->x -= 2;
        ship->pivot -= PIVOT_SPEED;
    }
    if (key[KEY_RIGHT]) {
        ship->x += 2;
        ship->pivot += PIVOT_SPEED;
    }
    if (key[KEY_UP]) {
        ship->y -= 2;
    }
    if (key[KEY_DOWN]) {
        ship->y += 2;
    }

    if (!key[KEY_LEFT] && !key[KEY_RIGHT]) {
        if (ship->pivot < PIVOT_CENTER) {
            ship->pivot += PIVOT_SPEED;
        }
        if (ship->pivot > PIVOT_CENTER) {
            ship->pivot -= PIVOT_SPEED;
        }
    }

    ship_limit_boundaries(ship);
    ship_set_pivot(ship);
}

/**
 * Set the ship's pivot frame. When moving to the left, the ship will
 * bank toward the left, and vice versa to the right. This is done when
 * the user holds a key (left, right) down for a while.
 *
 * When the user uses neither left nor right, the ship will return
 * to its regular center sprite.
 */
void ship_set_pivot(SHIP *ship) {
    int frame = ship->pivot / PIVOT_DIVIDER;
    switch (frame) {
        case 0:
            ship->curr_frame = &ship->cspr_l2;
            break;
        case 1:
            ship->curr_frame = &ship->cspr_l1;
            break;
        case 2:
            ship->curr_frame = &ship->cspr_m;
            break;
        case 3:
            ship->curr_frame = &ship->cspr_r1;
            break;
        case 4:
            ship->curr_frame = &ship->cspr_r2;
            break;
    }
}

/**
 * Limits the ship's x and y positions to buffer boundaries.
 * Should be called whenever updating the x and y positions
 * of the ship.
 */
void ship_limit_boundaries(SHIP *ship) {
    if (ship->x < 0) {
        ship->x = 0;
    }
    if (ship->y < 0) {
        ship->y = 0;
    }
    if (ship->x > scr_boundary_x - ship->w) {
        ship->x = scr_boundary_x - ship->w;
    }
    if (ship->y > scr_boundary_y - ship->h) {
        ship->y = scr_boundary_y - ship->h;
    }
    if (ship->pivot < 0) {
        ship->pivot = 0;
    }
    if (ship->pivot > PIVOT_MAX) {
        ship->pivot = PIVOT_MAX;
    }
}
