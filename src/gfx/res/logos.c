/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/res/logos.h"
#include "src/gfx/deps/manager.h"
#include "src/utils/counters.h"

int RES_ID_LAGAS;
char RES_PATH_LAGAS[] = "data\\res\\logos.dat";

void logos_register() {
    RES_ID_LAGAS = res_id();
    res_register(RES_ID_LAGAS, RES_PATH_LAGAS, 0);
}
