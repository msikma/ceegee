/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GAME_STATE__
#define __CEEGEE_GAME_STATE__

#define STATE_INITIAL 1
#define STATE_FLYING 2
#define STATE_EXIT 3
#define STATE_UNDETERMINED 4

int get_curr_state();
int get_next_state();
void advance_state();
void set_curr_state(int state);
void set_next_state(int state);

#endif
