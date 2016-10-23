/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <xorshift.h>
#include <stdint.h>
#include <math.h>

#include "src/gfx/starfield/algos.h"
#include "src/utils/math.h"

// List of algorithms.
void (*ALGORITHMS[])(float *x, float *y, int *n, int a, int b, float c) = {
    stars_random_f, stars_circle, stars_net, stars_circle_weird
};
// Total number of algorithms.
int ALGOS = sizeof(ALGORITHMS) / sizeof(int);

// Pointer to the repositioning algorithm currently in use.
void (*star_algo_ptr)(float *x, float *y, int *n, int a, int b, float c);

// Hardcoded values for the algorithms.
const int STARS_RANDOM_RADIUS = 64;
const int STARS_RANDOM_RADIUS_HALF = 32;
const int STARS_CIRCLE_LOOPS = 8;
const int STARS_CIRCLE_X_RADIUS = 24;
const int STARS_CIRCLE_Y_RADIUS = 40;
const int STARS_NET_X_RADIUS = 40;
const int STARS_NET_Y_RADIUS = 40;
const int STARS_ZIGZAG_RADIUS = 100;
const int STARS_ZIGZAG_RADIUS_HALF = 50;

/**
 * Randomly position the stars.
 *
 * This function is called with pointers to a star's x and y
 * positions, two ints a and b, which represent the current counter
 * value and the maximum counter value, and a float c which is a / b.
 * For example, if a = 0, this is the first frame that this algorithm
 * is in use. If a = 180 and b = 360, it's exactly the halfway point.
 */
void stars_random_f(float *x, float *y, int *n, int a, int b, float c) {
    float seed_x = xor32f();
    float seed_y = xor32f();
    float seed_z = xor32f();
    *x = (seed_x * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *y = (seed_y * STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
}

/**
 * Integer version of stars_random_f(). Currently unused.
 */
void stars_random_i(float *x, float *y, int *n, int a, int b, float c) {
    uint32_t seed = xor32();
    *x = (float)(seed % STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
    *y = (float)((seed >> 16) % STARS_RANDOM_RADIUS) - STARS_RANDOM_RADIUS_HALF;
}

/**
 * Draws stars in a circle.
 */
void stars_circle(float *x, float *y, int *n, int a, int b, float c) {
    int angle = deg_range((c - (0.11 * *n)) * STARS_CIRCLE_LOOPS * 180);
    *x = STARS_CIRCLE_X_RADIUS * degcos(angle);
    *y = STARS_CIRCLE_Y_RADIUS * degsin(angle);
}

/**
 * Draws several interlocking circles.
 */
void stars_circle_weird(float *x, float *y, int *n, int a, int b, float c) {
    int pos, deg;
    float mod;

    // Pos is set to 9 if it's 4, because 0.25 * 4 = 1, which would
    // cause the position to always be calculated as the same.
    pos = *n + 1;
    pos = pos != 4 ? pos : 9;
    mod = c - ((0.25 * c) * (pos));

    deg = deg_range(mod * STARS_CIRCLE_LOOPS * 180);

    *x = STARS_CIRCLE_X_RADIUS * degcos(deg);
    *y = STARS_CIRCLE_Y_RADIUS * degsin(deg);
}

/**
 * Creates a net pattern.
 */
void stars_net(float *x, float *y, int *n, int a, int b, float c) {
    int pos, deg;
    float mod, angle;

    pos = *n + 1;
    mod = (c * 2) - (0.14 * (pos));
    deg = deg_range(mod * 2 * 180);

    *x = STARS_NET_X_RADIUS * degcos(deg);
    *y = STARS_NET_Y_RADIUS * degsin(c * 360);
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
 *
 * Currently unused.
 */
void stars_zigzag(float *x, float *y, int *n, int a, int b, float c) {
    int half = a % 60;
    int whole = a % 120;
    float ypos = whole >= 60 ? ((60 - half) / 60.0) : (half / 60.0);
    *x = (STARS_ZIGZAG_RADIUS * c) - STARS_ZIGZAG_RADIUS_HALF;
    *y = (STARS_ZIGZAG_RADIUS * ypos) - STARS_ZIGZAG_RADIUS_HALF;
}
