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
    stars_random_f, stars_circle, stars_zigzag
};
// Total number of algorithms.
int ALGOS = sizeof(ALGORITHMS) / sizeof(int);

// Pointer to the repositioning algorithm currently in use.
int (*stars_algo_ptr)(float *x, float *y, int *z, int a, int b, float c);

// Hardcoded values for the algorithms.
const int STARS_RANDOM_RADIUS = 64;
const int STARS_RANDOM_RADIUS_HALF = 32;
const int STARS_CIRCLE_LOOPS = 8;
const int STARS_CIRCLE_X_RADIUS = 24;
const int STARS_CIRCLE_Y_RADIUS = 36;
const int STARS_ZIGZAG_RADIUS = 100;
const int STARS_ZIGZAG_RADIUS_HALF = 50;

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
    *x = (seed_x * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *y = (seed_y * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *z = 64 + (seed_z * 256);
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

/**
 * Draws stars in a circle.
 */
int stars_circle(float *x, float *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    float angle = c * STARS_CIRCLE_LOOPS * M_PI;
    *x = STARS_CIRCLE_X_RADIUS * cos(angle);
    *y = STARS_CIRCLE_Y_RADIUS * sin(angle);
    *z = 72 + (seed % 196);
}

/**
 * Creates a pattern like the following:
 *
 * \    /\    /\    /
 *  \  /  \  /  \  /
 *   \/    \/    \/
 *
 * The position of the zig zag is determined by the a and b values.
 * Currently it's hardcoded to depend on b having a value of 360.
 */
int stars_zigzag(float *x, float *y, int *z, int a, int b, float c) {
    uint32_t seed = xor32();
    int half = a % 60;
    int whole = a % 120;
    float ypos = whole >= 60 ? ((60 - half) / 60.0) : (half / 60.0);
    *x = (STARS_ZIGZAG_RADIUS * c) - STARS_ZIGZAG_RADIUS_HALF;
    *y = (STARS_ZIGZAG_RADIUS * ypos) - STARS_ZIGZAG_RADIUS_HALF;
    *z = 72 + (seed % 196);
}
