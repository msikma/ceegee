/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <xorshift.h>

#include "src/gfx/starfield/algos.h"

// List of algorithms.
int (*ALGORITHMS[])(int *x, int *y, int *z, int n, int m) = {
    //stars_random, stars_narrow, stars_angled
    stars_random
};
// Total number of algorithms.
int ALGOS = sizeof(ALGORITHMS) / sizeof(int);

// Pointer to the repositioning algorithm currently in use.
int (*stars_algo_ptr)(int *x, int *y, int *z, int n, int m);

/**
 * Randomly position the stars.
 *
 * This function is called with pointers to a star's initial x, y and z
 * positions, and two ints n and m, which represent the current counter
 * value and the maximum counter value. For example, if n = 0, this is
 * the first frame that this algorithm is in use. If n = 180 and m = 360,
 * it's exactly the halfway point.
 */
int stars_random(int *x, int *y, int *z, int n, int m) {
    uint32_t seed = xor32();
    *x = (seed % 96) - 48;
    *y = ((seed >> 16) % 96) - 48;
    *z = 128 + (seed % 256);
}

// todo
int stars_narrow(int *x, int *y, int *z, int n, int m) {
    uint32_t seed = xor32();
    *x = (seed % 22) - 11;
    *y = ((seed >> 16) % 22) - 11;
    *z = 128 + (seed % 256);
}

// todo
int stars_angled(int *x, int *y, int *z, int n, int m) {
    uint32_t seed = xor32();
    *x = (seed % 64) - 32;
    *y = (seed % 128) - 64;
    *z = 128 + (seed % 256);
}
