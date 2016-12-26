/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

#ifndef __CEEGEE_AUDIO_MIDI__
#define __CEEGEE_AUDIO_MIDI__

#define ERROR_INIT_SOUND 1
#define ERROR_LOADING_MUSIC 2

struct song {
    char name[63];
    char file[127];
    char author[63];
};
extern struct song MUSIC_LOGOS;
extern struct song MUSIC_WINTER_SONG;
extern struct song MUSIC_WHOA;
extern struct song MUSIC_IHSWSB;
extern struct song *ALL_MUSIC[];
extern int ALL_MUSIC_AMOUNT;
int initialize_sound();
int music_start(struct song *reqsong);
int music_stop();
MIDI *the_music;

#endif
