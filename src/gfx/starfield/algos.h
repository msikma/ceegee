/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_STARFIELD_ALGOS__
#define __CEEGEE_GFX_STARFIELD_ALGOS__

extern int (*ALGORITHMS[])(int *x, int *y, int *z, int n, int m);
extern int (*stars_algo_ptr)(int *x, int *y, int *z, int n, int m);
extern int ALGOS;
int stars_angled(int *x, int *y, int *z, int n, int m);
int stars_narrow(int *x, int *y, int *z, int n, int m);
int stars_random(int *x, int *y, int *z, int n, int m);

#endif
