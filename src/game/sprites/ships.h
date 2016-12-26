/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>
#include <allegro.h>

#ifndef __CEEGEE_GAME_SHIPS_USP_TALON__
#define __CEEGEE_GAME_SHIPS_USP_TALON__

#define USP_TALON 1

#define PIVOT_MAX 319
#define PIVOT_CENTER 159
#define PIVOT_DIVIDER 64
#define PIVOT_SPEED 13

typedef struct SHIP {
    int x, y, w, h;
    int pivot;
    COMPILED_SPRITE *cspr_m, *cspr_l1, *cspr_l2, *cspr_r1, *cspr_r2;
    COMPILED_SPRITE **curr_frame;
} SHIP;

SHIP ship_create();
void ship_draw(SHIP *ship, BITMAP *buffer);
void ship_feed_input(SHIP *ship);
void ship_limit_boundaries(SHIP *ship);
void ship_set_pivot(SHIP *ship);
void ship_set_pos(SHIP *ship, int x, int y);

#endif
