/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <xorshift.h>
#include <stdint.h>
#include <math.h>

#include "src/gfx/starfield/algos.h"

// List of algorithms.
int (*ALGORITHMS[])(int *x, int *y, int *z, int a, int b, float c) = {
    //stars_random, stars_narrow, stars_angled
    stars_narrow
    //stars_random
};
// Total number of algorithms.
int ALGOS = sizeof(ALGORITHMS) / sizeof(int);

// Pointer to the repositioning algorithm currently in use.
int (*stars_algo_ptr)(int *x, int *y, int *z, int a, int b, float c);

/**
 * Randomly position the stars.
 *
 * This function is called with pointers to a star's initial x, y and z
 * positions, two ints a and b, which represent the current counter
 * value and the maximum counter value, and a float c which is a / b.
 * For example, if a = 0, this is the first frame that this algorithm
 * is in use. If a = 180 and b = 360, it's exactly the halfway point.
 */
int stars_random(int *x, int *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    *x = (seed % 36) - 18;
    *y = ((seed >> 16) % 36) - 18;
    *z = 72 + (seed % 196);
}

int stars_narrow(int *x, int *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    int gap = 6;// * (fabsf((c * 2) - 1) + 0.1);
    //*x = (n % 36) - 18;
    //*y = ((1.0 * n / m) * 50.0) - 25;
    *x = (seed % gap) - (gap / 2);
    *y = ((seed >> 16) % gap) - (gap / 2);
    *z = 72 + (seed % 196);
}

// todo
int stars_angled(int *x, int *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    *x = (seed % 64) - 32;
    *y = (seed % 128) - 64;
    *z = 128 + (seed % 256);
}
