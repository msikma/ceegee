/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_BITMAPS__
#define __CEEGEE_GFX_BITMAPS__

void fade_in_bitmap(char *file);
void fade_in_data_bmp(BITMAP *image, RGB *pal);
void fade_out_bitmap();
void show_bitmaps();
void show_startup_logos();

#endif
