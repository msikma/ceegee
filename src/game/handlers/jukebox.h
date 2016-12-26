/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdbool.h>

#ifndef __CEEGEE_GAME_HANDLERS_JUKEBOX__
#define __CEEGEE_GAME_HANDLERS_JUKEBOX__

#define JUKEBOX_EXIT 1
#define JUKEBOX_NEXT_SONG 2
#define JUKEBOX_PREV_SONG 3

void finish_song();
void prev_song();
void next_song();
void draw_help();
void update_song_data();
void update_track_data();
void jukebox_deps();
void jukebox_init();
void jukebox_update();
void jukebox_render();
bool jukebox_will_exit();
void jukebox_exit();

#endif
