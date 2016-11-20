/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/audio/midi.h"
#include "src/game.h"

// Whether the Allegro sound driver is initialized.
int ALLEGRO_SOUND_INITIALIZED = FALSE;

// Displayed alongside the logos when starting the game.
struct song MUSIC_LOGOS = {
    "What is this 2",
    "data\\music\\wit2.mid",
    "Chef Boyardee"
};
// Test music.
struct song MUSIC_WINTER_SONG = {
    "Winter Song",
    "data\\music\\wtsong.mid",
    "Chef Boyardee"
};
struct song MUSIC_WHOA = {
    "Whoa",
    "data\\music\\whoa.mid",
    "Chef Boyardee"
};
struct song MUSIC_IHSWSB = {
    "I_had_Sex_with_Sling_Blade",
    "data\\music\\ihswsb.mid",
    "Chef Boyardee"
};


// Complete list of all music.
struct song *ALL_MUSIC[] = {
    &MUSIC_LOGOS,
    &MUSIC_WINTER_SONG,
    &MUSIC_WHOA,
    &MUSIC_IHSWSB
};

int ALL_MUSIC_AMOUNT = sizeof(ALL_MUSIC) / sizeof(ALL_MUSIC[0]);

MIDI *curr_music;

/**
 * Installs the Allegro sound driver.
 */
int initialize_sound() {
    if (ALLEGRO_SOUND_INITIALIZED == TRUE) {
        return 0;
    }
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        // Cannot initialize sound system.
        return ERROR_INIT_SOUND;
    }
    ALLEGRO_SOUND_INITIALIZED = TRUE;
    return 0;
}

/**
 * Initializes a midi file and begins playback.
 * Returns ERROR_INIT_SOUND or ERROR_LOADING_MUSIC on errors.
 */
int music_start(struct song *reqsong) {
    int length, pos;
    int done = 0;

    initialize_sound();

    curr_music = load_midi(reqsong->file);
    if (!curr_music) {
        // Cannot load midi file.
        return ERROR_LOADING_MUSIC;
    }
    length = get_midi_length(curr_music);

    play_midi(curr_music, TRUE);

    return 0;
}

/**
 * Stops midi playback and removes the file from memory.
 */
int music_stop() {
    destroy_midi(curr_music);
    return 0;
}
