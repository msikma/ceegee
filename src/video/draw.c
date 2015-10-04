/*
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <sys/nearptr.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

#include "draw.h"
#include "../types.h"

/**
 * Sets the base offset for the VGA and system clock pointers.
 */
void set_base_addr()
{
    // Pointer to the video memory.
    VGA = (byte *)VGA_ADDR + __djgpp_conventional_base;
    // The 18.2hz internal clock.
    SYS_CLOCK = (void *)SYS_CLOCK_ADDR + __djgpp_conventional_base;
}

/**
 * Enables access to near pointers; exits the program with an error in case
 * we aren't able to access them.
 * <http://www.delorie.com/djgpp/doc/libc/libc_141.html>
 */
void enable_nearptr()
{
    if (__djgpp_nearptr_enable() == 0) {
        clrscr();
        printf("Could not access the first 640K of memory.\n");
        printf("Ensure you're running this program in MSDOS.\n");
        exit(-1);
    }
}

/**
 * Disables access to near pointers.
 */
void disable_nearptr()
{
    __djgpp_nearptr_disable();
}

/**
 * Writes a single pixel directly to the video memory.
 */
void plot_pixel(int x, int y, byte color)
{
    VGA[(y << 8) + (y << 6) + x] = color;
}

/**
 * Sets the VGA mode, unless the requested mode has already been set.
 */
void set_mode(byte mode)
{
    union REGS regs;

    // Don't change the mode if we're already using it,
    // or if we're still on text mode without having switched prior to this.
    if (mode == curr_mode || (mode == TEXT_MODE && !curr_mode)) {
        return;
    }
    curr_mode = mode;

    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT, &regs, &regs);
}
