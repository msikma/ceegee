/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

// Datafile indices for flim.dat.
#define FLIM_GRAY 0
#define FLIM_WHITE 1

extern DATAFILE *FLIM;
extern int FLIM_HEIGHT;

int load_flim();
int unload_flim();
void add_flim_palette_colors(RGB *pal);
