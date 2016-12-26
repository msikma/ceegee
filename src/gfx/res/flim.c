/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/flim.h"
#include "src/gfx/deps/manager.h"
#include "src/utils/counters.h"

int RES_ID_FLIM;
char RES_PATH_FLIM[] = "data\\res\\font\\flim.dat";

int FLIM_HEIGHT;
DATAFILE* data;

void flim_register() {
    RES_ID_FLIM = res_id();
    res_register(RES_ID_FLIM, RES_PATH_FLIM, flim_callback);
}

void flim_callback() {
    data = dep_data_ref(RES_ID_FLIM);
    FLIM_HEIGHT = text_height(data[FLIM_WHITE].dat) - 4;
}
