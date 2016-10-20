/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_GFX_STARFIELD_ALGOS__
#define __CEEGEE_GFX_STARFIELD_ALGOS__

extern int (*ALGORITHMS[])(float *x, float *y, int *z, int a, int b, float c);
extern int (*stars_algo_ptr)(float *x, float *y, int *z, int a, int b, float c);
extern int ALGOS;
int stars_angled(float *x, float *y, int *z, int a, int b, float c);
int stars_narrow(float *x, float *y, int *z, int a, int b, float c);
int stars_random_f(float *x, float *y, int *z, int a, int b, float c);
int stars_random_i(float *x, float *y, int *z, int a, int b, float c);

#endif
