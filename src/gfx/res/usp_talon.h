/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_RES_USP_TALON__
#define __CEEGEE_GFX_RES_USP_TALON__

#include "src/gfx/res/data/usp_talon_data.h"

extern DATAFILE *USP_TALON_DAT;
int load_usp_talon_dat();
static char USP_TALON_PATH[] = "data\\res\\usptalon.dat";
void unload_usp_talon_dat();

#endif
