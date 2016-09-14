/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>

#include "src/utils/version.h"

/**
 * Returns the version of the program. The CEEGEE_VERSION macro
 * is set on compile time. See Makefile for details.
 */
const char *get_version() {
    return CEEGEE_VERSION;
}

/**
 * Returns the name of the program. See get_version().
 */
const char *get_name() {
    return CEEGEE_NAME;
}

/**
 * Returns the copyright string. See get_version().
 */
const char *get_copyright() {
    return CEEGEE_COPYRIGHT;
}

/**
 * Returns the URL string. See get_version().
 */
const char *get_url() {
    return CEEGEE_URL;
}

/**
 * Prints the version.
 */
void print_version() {
    printf("%s", get_version());
}
