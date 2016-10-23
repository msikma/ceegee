/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_TEXT__
#define __CEEGEE_GFX_TEXT__

#define TXT_LEFT 0
#define TXT_CENTER 1
#define TXT_RIGHT 2
#define TXT_WHITE -1
#define TXT_GRAY -2
#define TXT_REGULAR 5

void draw_textf(BITMAP *buffer, int x, int y, int color_a, int color_b,
    int bg, int font, int align, const char *format, ...);
void draw_text(BITMAP *buffer, int x, int y, int color_a, int color_b,
    int bg, int font, int align, char txt[512]);

#endif
