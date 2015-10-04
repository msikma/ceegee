/*
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdlib.h>

#include "../video/draw.h"

/**
 * Seeds the random number generator using the system clock.
 */
void seed_prng()
{
    srand(*SYS_CLOCK);
}

/**
 * Executes startup procedures. Used once at the start of the program.
 */
void startup_proc()
{
    set_base_addr();
    seed_prng();
}

/**
 * Executes shutdown procedures. Used before exiting back to DOS.
 */
void shutdown_proc()
{
    // Disable near pointers.
    disable_nearptr();
    
    // Go back to text mode for DOS if we're not using it already.
    set_mode(TEXT_MODE);
}
