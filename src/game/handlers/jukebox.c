/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/audio/midi.h"
#include "src/game.h"
#include "src/game/handlers/jukebox.h"
#include "src/game/loop/state.h"
#include "src/gfx/bitmaps.h"
#include "src/gfx/deps/manager.h"
#include "src/gfx/deps/register.h"
#include "src/gfx/modes.h"
#include "src/gfx/res/flim.h"
#include "src/gfx/starfield/starfield.h"
#include "src/gfx/text.h"
#include "src/utils/counters.h"

int REQ_ID_JUKEBOX_HANDLER;

// Track that's currently playing.
struct song *curr_track;
MIDI *curr_music;
// Whether the current track is finished. True initially.
bool is_finished = true;

// What to do on each loop iteration.
int task = 0;

// How long (in ms) between updates of the on-screen text.
const int UPDATE_FREQUENCY = 150;

// Help text.
char HELP_EXIT[] = "Press ESC to exit";
char HELP_ARROWS[] = "Use arrow keys to choose another song";

// Help text drawing information.
int font_height = 0;
int help_text_x = 0;
int help_text_y1 = 0;
int help_text_y2 = 0;
int help_text_y3 = 0;
int help_text_y4 = 0;

// Total length and number of beats (quarter notes) in the song.
int length, beats;
int track_n = 0;

/**
 * Draws two lines of help text on the screen to show the user
 * how to use the jukebox.
 */
void draw_help(BITMAP *buffer) {
    draw_text(buffer, help_text_x, help_text_y1, TXT_GRAY, -1, -1,
        TXT_REGULAR, TXT_CENTER, HELP_EXIT);
    draw_text(buffer, help_text_x, help_text_y2, TXT_GRAY, -1, -1,
        TXT_REGULAR, TXT_CENTER, HELP_ARROWS);
}

/**
 * Updates the display to show what song is currently playing.
 */
void update_song_data(BITMAP *buffer) {
    draw_textf(buffer, help_text_x, help_text_y3, TXT_WHITE, -1, -1,
        TXT_REGULAR, TXT_CENTER, "%d/%d: %s", track_n + 1,
        ALL_MUSIC_AMOUNT, curr_track->name);
}

/**
 * Draws the current time and duration of the song to the screen.
 */
void update_track_data(BITMAP *buffer) {
    draw_textf(buffer, help_text_x, help_text_y4, TXT_WHITE, -1, -1,
        TXT_REGULAR, TXT_CENTER, "%ld:%02ld/%d:%02d", midi_time / 60,
        midi_time % 60, length / 60, length % 60);
}

/**
 * Request the jukebox handler dependencies.
 */
void jukebox_deps() {
    REQ_ID_JUKEBOX_HANDLER = req_id();
    dep_require(RES_ID_FLIM, REQ_ID_JUKEBOX_HANDLER);
}

/**
 * Initialize the jukebox handler.
 *
 * This handler is used when the game boots up. It sets up whatever
 * needs to be done for the game globally and then hands over control
 * to the next handler.
 */
void jukebox_init() {
    // Prepare for the jukebox loop.
    RGB *pal = get_starfield_palette();
    add_text_colors(pal);
    set_palette(pal);
    free(pal);

    initialize_starfield();

    font_height = FLIM_HEIGHT;
    help_text_x = SCREEN_W / 2;
    help_text_y1 = SCREEN_H - (font_height * 5) - (font_height / 2);
    help_text_y2 = SCREEN_H - (font_height * 4) - (font_height / 2);
    help_text_y3 = SCREEN_H - (font_height * 3);
    help_text_y4 = SCREEN_H - (font_height * 2);
}

/**
 * Unload the currently playing song and indicate that we need the next.
 */
void finish_song() {
    is_finished = true;
    destroy_midi(curr_music);
}

/**
 * Advance to the next song; loop back to zero if we're at the end.
 */
void next_song() {
    if (++track_n >= ALL_MUSIC_AMOUNT) {
        track_n = 0;
    }
    finish_song();
}

/**
 * Go back to the previous song.
 */
void prev_song() {
    if (--track_n < 0) {
        track_n = ALL_MUSIC_AMOUNT - 1;
    }
    finish_song();
}

/**
 * Update the internal state of the jukebox handler.
 */
void jukebox_update() {
    int key_p;

    while (keypressed()) {
        key_p = readkey() >> 8;
        if (key_p == KEY_LEFT) {
            task = JUKEBOX_PREV_SONG;
        }
        if (key_p == KEY_RIGHT) {
            task = JUKEBOX_NEXT_SONG;
        }
    }

    if (task == JUKEBOX_NEXT_SONG) {
        next_song();
    }
    if (task == JUKEBOX_PREV_SONG) {
        prev_song();
    }

    // Done with the current task, so wait until the next one.
    task = 0;

    // Load up a new midi file if we're not playing anything.
    if (is_finished) {
        curr_track = ALL_MUSIC[track_n];

        // Load the next midi file.
        curr_music = load_midi(curr_track->file);
        length = get_midi_length(curr_music);
        // After calling get_midi_length(), midi_pos will contain the negative
        // number of beats, and midi_time the length of the midi in seconds.
        beats = -midi_pos;

        // Begin playback.
        play_midi(curr_music, FALSE);
        is_finished = false;
    }

    // When we're at the end of the file, midi_pos will be set to
    // the negative number of beats in the song.
    if (midi_pos < 0) {
        is_finished = true;
        task = JUKEBOX_NEXT_SONG;
    }
}

/**
 * Renders the output of the jukebox handler's current game state.
 */
void jukebox_render(BITMAP *buffer) {
    clear_bitmap(buffer);
    update_starfield(buffer);
    update_track_data(buffer);
    update_song_data(buffer);
    draw_help(buffer);
    vsync();
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

/**
 * Whether or not the jukebox handler will shutdown and exit.
 */
bool jukebox_will_exit() {
    if (key[KEY_ESC]) {
        return true;
    }
    return false;
}

/**
 * Shutdown and exit the jukebox handler.
 */
void jukebox_exit() {
    dep_forget(RES_ID_FLIM, REQ_ID_JUKEBOX_HANDLER);
    set_next_state(STATE_EXIT);
}
