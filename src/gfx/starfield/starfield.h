/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <inttypes.h>

#ifndef __CEEGEE_GFX_STARFIELD_STARFIELD__
#define __CEEGEE_GFX_STARFIELD_STARFIELD__

// Each visualization of the starfield is shown for this number
// of counter ticks, then the next one begins.
// Changing this will prevent some visualizations from working correctly.
#define COUNTER_MAX 360

int loop_starfield(BITMAP *buffer);
int star_hue_color(int n);
RGB *get_starfield_palette();
void draw_star(BITMAP *buffer, int x, int y, int c);
void draw_starfield(BITMAP *buffer);
void initialize_star_positions();
void initialize_starfield();
void move_starfield();
void set_star_pos_algo();
void update_starfield_counter();
void update_starfield(BITMAP *buffer);

#endif
