/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "src/gfx/res/data/flim_data.h"

#define FLIM_WHITE FLIM_W_PCX
#define FLIM_GRAY FLIM_G_PCX

extern DATAFILE *FLIM;
extern int FLIM_HEIGHT;

int load_flim();
int unload_flim();
void add_flim_palette_colors(RGB *pal);
