/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_RES_FLIM__
#define __CEEGEE_GFX_RES_FLIM__

#include "src/gfx/res/data/flim_data.h"

extern DATAFILE *FLIM;
extern int FLIM_HEIGHT;

int load_flim_dat();
int unload_flim_dat();
static char FLIM_PATH[] = "data\\res\\font\\flim.dat";
void add_flim_palette_colors(RGB *pal);

#endif
