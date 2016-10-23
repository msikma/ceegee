/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>

#include "src/gfx/text.h"
#include "src/gfx/res/flim.h"

/**
 * Draws text, with formatting.
 */
void draw_textf(BITMAP *buffer, int x, int y, int color_a, int color_b,
    int bg, int font, int align, const char *format, ...)
{
    char txt[TXT_MAX_SIZE];
    va_list ap;

    // String formatting.
    va_start(ap, format);
    uvszprintf(txt, sizeof(txt), format, ap);
    va_end(ap);

    draw_text(buffer, x, y, color_a, color_b, bg, font, align, txt);
}

/**
 * Draws text. TODO: explain
 * TXT_WHITE
 */
void draw_text(BITMAP *buffer, int x, int y, int color_a, int color_b,
    int bg, int font, int align, char txt[TXT_MAX_SIZE])
{
    void (*txt_fn)() = 0;

    // Assign the text drawing function based on alignment.
    switch (align) {
        case TXT_LEFT:
            txt_fn = textout_ex;
            break;
        case TXT_CENTER:
            txt_fn = textout_centre_ex;
            break;
        case TXT_RIGHT:
            txt_fn = textout_right_ex;
            break;
    }

    // Set text color; either the desired colors were passed directly,
    // or color_a was set to e.g. TXT_WHITE. If it's the latter,
    // set the true colors here.
    // Note, all predefined colors have a value of less than zero.
    if (color_a < 0) {
        switch (color_a) {
            case TXT_WHITE:
                color_a = palette_color[254];
                color_b = palette_color[253];
                break;
            case TXT_GRAY:
                color_a = palette_color[253];
                color_b = palette_color[252];
                break;
        }
    }

    switch (font) {
        case TXT_REGULAR:
            txt_fn(buffer, FLIM[FLIM_WHITE].dat, txt, x, y, color_a, bg);
            txt_fn(buffer, FLIM[FLIM_GRAY].dat, txt, x, y, color_b, bg);
    }
}
