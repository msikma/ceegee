/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_STARFIELD_ALGOS__
#define __CEEGEE_GFX_STARFIELD_ALGOS__

extern int (*ALGORITHMS[])(int *x, int *y, int *z, int a, int b, float c);
extern int (*stars_algo_ptr)(int *x, int *y, int *z, int a, int b, float c);
extern int ALGOS;
int stars_angled(int *x, int *y, int *z, int a, int b, float c);
int stars_narrow(int *x, int *y, int *z, int a, int b, float c);
int stars_random(int *x, int *y, int *z, int a, int b, float c);

#endif
