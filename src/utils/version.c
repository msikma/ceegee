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
const char * get_version() {
    return CEEGEE_VERSION;
}

/**
 * Prints the version.
 */
void print_version() {
    printf("%s", get_version());
}
