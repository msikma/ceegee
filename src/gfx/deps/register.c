/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "src/gfx/res/flim.h"
#include "src/gfx/res/logos.h"
#include "src/gfx/res/tin.h"
#include "src/gfx/res/usp_talon.h"

/**
 * Asks every resource to register itself.
 */
void register_resources() {
    usp_talon_register();
    logos_register();

    // Fonts:
    flim_register();
    tin_register();
}
