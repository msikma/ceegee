/*
 * test/vga_test.c - small test subroutine to verify the VGA.
 * Taken from the excellent VGA tutorials by David Brackeen.
 * <http://www.brackeen.com/vga/shapes.html>
 *
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>, David Brackeen
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>

#include "../types.h"
#include "../utils/fn.h"
#include "../video/draw.h"

/**
 * Plots a line using Bresenham's line-drawing algorithm, which uses
 * no multiplication or division.
 */
void plot_line(int x1, int y1, int x2, int y2, byte color)
{
    int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

    dx = x2 - x1;
    dy = y2 - y1;
    dxabs = abs(dx);
    dyabs = abs(dy);
    sdx = sgn(dx);
    sdy = sgn(dy);
    x = dyabs >> 1;
    y = dxabs >> 1;
    px = x1;
    py = y1;

    plot_pixel(px, py, color);

    if (dxabs >= dyabs) {
        /* the line is more horizontal than vertical */
        for (i = 0; i < dxabs; i++) {
            y += dyabs;
            if (y >= dxabs) {
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            plot_pixel(px, py, color);
        }
    }
    else {
        /* the line is more vertical than horizontal */
        for (i = 0; i < dyabs; i++) {
            x += dxabs;
            if (x>=dyabs) {
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            plot_pixel(px, py, color);
        }
    }
}

/**
 * Returns a random color from the standard 13h colors.
 */
static int rand_color()
{
    return rand() % MODE_13H_NUM_COLORS;
}

/**
 * Runs a small test to ensure the VGA is working. This will set the mode
 * to 13h and back to text, so it's designed to assume we're currently in
 * text mode and want to go back to that mode afterwards.
 */
void run_vga_test()
{
    int x1, y1, x2, y2, color, n;
    int lines = 5000;
    float duration;
    word start;

    // Set the video mode to 13h.
    set_mode(MODE_13H_CODE);

    start = *SYS_CLOCK;

    // Draw 5000 lines randomly.
    for (n = 0; n < lines; n++) {
        x1=rand() % MODE_13H_WIDTH;
        y1=rand() % MODE_13H_HEIGHT;
        x2=rand() % MODE_13H_WIDTH;
        y2=rand() % MODE_13H_HEIGHT;
        color = rand_color();
        plot_line(x1, y1, x2, y2, color);
    }

    duration = (*SYS_CLOCK - start) / SYS_CLOCK_HZ;

    set_mode(TEXT_MODE);
    printf("Took %f seconds to draw %i lines.\n", duration, lines);
}
