/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_RES_TIN__
#define __CEEGEE_GFX_RES_TIN__

#include "src/gfx/res/data/tin_data.h"

extern DATAFILE *TIN_DAT;
extern int TIN_HEIGHT;
int load_tin_dat();
static char TIN_PATH[] = "data\\res\\font\\tin.dat";
void add_tin_palette_colors(RGB *pal);
void unload_tin_dat();

#endif
