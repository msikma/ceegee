/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_RES_LOGOS__
#define __CEEGEE_GFX_RES_LOGOS__

#include "src/gfx/res/data/logos_data.h"

extern DATAFILE *LOGOS;
extern int STARTUP_LOGO_BMP[];
extern int STARTUP_LOGO_PAL[];
extern int STARTUP_LOGOS;

int load_logos_dat();
int unload_logos_dat();
static char LOGOS_PATH[] = "data\\res\\logos.dat";

#endif
