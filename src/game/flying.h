/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>

#ifndef __CEEGEE_GAME_FLYING__
#define __CEEGEE_GAME_FLYING__

void flying_init();
void flying_update();
void flying_render();
bool flying_will_exit();
void flying_exit();

#endif
