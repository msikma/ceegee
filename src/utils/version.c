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
 * Returns the short version.
 */
const char *get_short_version() {
    return CEEGEE_SHORT_VERSION;
}

/**
 * Returns the name of the program.
 */
const char *get_name() {
    return CEEGEE_NAME;
}

/**
 * Returns the copyright string.
 */
const char *get_copyright() {
    return CEEGEE_COPYRIGHT;
}

/**
 * Returns the URL string.
 */
const char *get_url() {
    return CEEGEE_URL;
}

/**
 * Returns an info string (one line) about the OS used to compile this release.
 */
const char *get_os_info() {
    return CEEGEE_OSINFO;
}

/**
 * Returns an info string (one line) about the compiler used for this release.
 */
const char *get_cc_info() {
    return CEEGEE_CCINFO;
}

/**
 * Returns the CFLAGS used during compile time.
 */
const char *get_cflags() {
    return CEEGEE_CFLAGS;
}

/**
 * Returns the LDFLAGS used during compile time.
 */
const char *get_ldflags() {
    return CEEGEE_LDFLAGS;
}

/**
 * Returns the build time and date.
 */
const char *get_build_time() {
    return CEEGEE_BUILDTIME;
}

/**
 * Prints the version.
 */
void print_version() {
    printf("%s", get_version());
}
