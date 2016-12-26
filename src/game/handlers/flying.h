/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>

#ifndef __CEEGEE_GAME_HANDLERS_FLYING__
#define __CEEGEE_GAME_HANDLERS_FLYING__

extern int REQ_ID_FLYING_HANDLER;

void flying_deps();
void flying_init();
void flying_update();
void flying_render();
bool flying_will_exit();
void flying_exit();

#endif
