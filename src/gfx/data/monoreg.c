/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

DATAFILE *MONOREG;
int MONOREG_LOADED = 0;

int load_monoreg() {
    if (MONOREG_LOADED == 1) {
        return 0;
    }
    MONOREG = load_datafile("data\\font\\monoreg.dat");

    if (!MONOREG) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading ");
        return 1;
    }

    MONOREG_LOADED = 1;
    return 0;
}
