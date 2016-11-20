/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>

#ifndef __CEEGEE_GAME_HANDLERS_LOGOS__
#define __CEEGEE_GAME_HANDLERS_LOGOS__

static void show_startup_logos();
void logos_init();
void logos_update();
void logos_render();
bool logos_will_exit();
void logos_exit();

#endif
