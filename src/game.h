/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GAME__
#define __CEEGEE_GAME__

#define CEEGEE_SCR_W 320
#define CEEGEE_SCR_H 200

int initialize();
int screen_gfx_mode();
int screen_text_mode();
int start_game();
void shutdown();

#endif
