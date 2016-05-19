/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "midi.h"
#include "game.h"

MIDI *the_music;

/**
 * Initializes a midi file and begins playback.
 * Returns ERROR_INIT_SOUND or ERROR_LOADING_MUSIC on errors.
 */
int music_start(char *name) {
    initialize();

    int length, pos;
    int done = 0;

    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        // Cannot initialize sound system.
        return ERROR_INIT_SOUND;
    }

    the_music = load_midi(name);
    if (!the_music) {
        // Cannot load midi file.
        return ERROR_LOADING_MUSIC;
    }
    length = get_midi_length(the_music);

    play_midi(the_music, TRUE);

    return 0;
}

/**
 * Stops midi playback and removes the file from memory.
 */
int music_stop() {
    destroy_midi(the_music);
    return 0;
}
