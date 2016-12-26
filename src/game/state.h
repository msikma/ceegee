/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GAME_STATE__
#define __CEEGEE_GAME_STATE__

typedef struct game_state_obj {
    int loop_state_post_init;
} game_state_obj;

extern game_state_obj game_state;

void initialize_game_state();

#endif
