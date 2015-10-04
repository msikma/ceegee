/*
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "../types.h"

#ifndef __CEEGEE_DRAW_VIDEO__
#define __CEEGEE_DRAW_VIDEO__

#define VGA_ADDR            0xA0000 // VGA memory address
#define SYS_CLOCK_ADDR      0x046C  // System clock memory address
#define SYS_CLOCK_HZ        18.2    // The system clock is 18.2 hz.
#define SET_MODE            0x00    // BIOS function to set the video mode.
#define VIDEO_INT           0x10    // BIOS video interrupt.
#define TEXT_MODE           0x03    // Sets 80x25 text mode.
#define MODE_13H_CODE       0x13    // Sets 256 VGA color mode.
#define MODE_13H_NUM_COLORS 256     // Number of colors in mode 13h.
#define MODE_13H_WIDTH      320     // Screen width in mode 13h.
#define MODE_13H_HEIGHT     200     // Screen height in mode 13h.

byte *VGA;
word *SYS_CLOCK;
byte curr_mode;
void plot_pixel(int x, int y, byte color);
void set_base_addr();
void set_mode(byte mode);
void enable_nearptr();
void disable_nearptr();

#endif
