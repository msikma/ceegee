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
char MUSIC_LOGOS[] = "data\\music\\wit2.mid";
// Test music.
char MUSIC_RONDO[] = "data\\music\\rondo.mid";

// Complete list of all music.
char *ALL_MUSIC[] = {
    MUSIC_LOGOS,
    MUSIC_RONDO
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
}

/**
 * Initializes a midi file and begins playback.
 * Returns ERROR_INIT_SOUND or ERROR_LOADING_MUSIC on errors.
 */
int music_start(char *name) {
    initialize();

    int length, pos;
    int done = 0;

    initialize_sound();

    curr_music = load_midi(name);
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
