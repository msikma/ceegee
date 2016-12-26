/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/tin.h"
#include "src/gfx/deps/manager.h"
#include "src/utils/counters.h"

int RES_ID_TIN;
char RES_PATH_TIN[] = "data\\res\\font\\tin.dat";

int TIN_HEIGHT;
DATAFILE* data;

void tin_register() {
    RES_ID_TIN = res_id();
    res_register(RES_ID_TIN, RES_PATH_TIN, tin_callback);
}

void tin_callback() {
    data = dep_data_ref(RES_ID_TIN);
    TIN_HEIGHT = text_height(data[TIN_WHITE].dat) - 4;
}
