/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

#ifndef __CEEGEE_MIDI__
#define __CEEGEE_MIDI__

int music_start();
int music_stop();

MIDI *the_music;

#define ERROR_INIT_SOUND 1
#define ERROR_LOADING_MUSIC 2

#endif
