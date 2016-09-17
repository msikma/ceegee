/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_JUKEBOX__
#define __CEEGEE_JUKEBOX__

#define JUKEBOX_EXIT 1
#define JUKEBOX_NEXT_SONG 2
#define JUKEBOX_PREV_SONG 3

int jukebox_loop();
int start_jukebox();
void draw_help();
void initialize_jukebox();
void update_song_data();
void update_track_data();

#endif
