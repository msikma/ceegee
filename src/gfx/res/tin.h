/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

#ifndef __CEEGEE_GFX_RES_TIN__
#define __CEEGEE_GFX_RES_TIN__

#include "src/gfx/res/data/tin_data.h"

extern int TIN_HEIGHT;
extern int RES_ID_TIN;
void tin_add_palette(RGB *pal);
void tin_callback();
void tin_register();

#endif
