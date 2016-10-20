/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <xorshift.h>
#include <stdint.h>
#include <math.h>

#include "src/gfx/starfield/algos.h"

// List of algorithms.
int (*ALGORITHMS[])(float *x, float *y, int *z, int a, int b, float c) = {
    //stars_random, stars_narrow, stars_angled
    //stars_narrow
    stars_random_f
};
// Total number of algorithms.
int ALGOS = sizeof(ALGORITHMS) / sizeof(int);

// Pointer to the repositioning algorithm currently in use.
int (*stars_algo_ptr)(float *x, float *y, int *z, int a, int b, float c);

// Radius of the stars_random() algorithm.
const int STARS_RANDOM_RADIUS = 64;
const int STARS_RANDOM_RADIUS_HALF = 32;

/**
 * Randomly position the stars.
 *
 * This function is called with pointers to a star's initial x, y and z
 * positions, two ints a and b, which represent the current counter
 * value and the maximum counter value, and a float c which is a / b.
 * For example, if a = 0, this is the first frame that this algorithm
 * is in use. If a = 180 and b = 360, it's exactly the halfway point.
 */
int stars_random_f(float *x, float *y, int *z, int a, int b, float c) {
    float seed_x = xor32f();
    float seed_y = xor32f();
    float seed_z = xor32f();
    *x = (float)(seed_x * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *y = (float)(seed_y * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *z = (int)64 + (seed_z * 256);
}

/**
 * Integer version of stars_random_f(). Currently unused.
 */
int stars_random_i(float *x, float *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    *x = (float)(seed % STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *y = (float)((seed >> 16) % STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *z = 72 + (seed % 196);
}

int stars_narrow(float *x, float *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    int gap = 6;// * (fabsf((c * 2) - 1) + 0.1);
    //*x = (n % 36) - 18;
    //*y = ((1.0 * n / m) * 50.0) - 25;
    *x = (seed % gap) - (gap / 2);
    *y = ((seed >> 16) % gap) - (gap / 2);
    *z = 72 + (seed % 196);
}

// todo
int stars_angled(float *x, float *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    *x = (seed % 64) - 32;
    *y = (seed % 128) - 64;
    *z = 128 + (seed % 256);
}
