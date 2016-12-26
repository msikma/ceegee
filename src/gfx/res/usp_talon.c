/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/usp_talon.h"
#include "src/gfx/deps/manager.h"
#include "src/utils/counters.h"

int RES_ID_USP_TALON;
char RES_PATH_USP_TALON[] = "data\\res\\usptalon.dat";

DATAFILE* data;

void usp_talon_register() {
    RES_ID_USP_TALON = res_id();
    res_register(RES_ID_USP_TALON, RES_PATH_USP_TALON, 0);
}
