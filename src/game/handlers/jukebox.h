/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>

#ifndef __CEEGEE_GAME_HANDLERS_JUKEBOX__
#define __CEEGEE_GAME_HANDLERS_JUKEBOX__

void jukebox_deps();
void jukebox_init();
void jukebox_update();
void jukebox_render();
bool jukebox_will_exit();
void jukebox_exit();

#endif
