/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_RES_TEST_SPRITE__
#define __CEEGEE_GFX_RES_TEST_SPRITE__

#include "src/gfx/res/data/test_sprite_data.h"

extern DATAFILE *TEST_SPRITE_DAT;
int load_test_sprite_dat();
static char TEST_SPRITE_PATH[] = "data\\res\\tstspr.dat";
void unload_test_sprite_dat();

#endif
