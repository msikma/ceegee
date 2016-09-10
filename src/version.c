/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "version.h"

/**
 * Returns the version of the program. The CEEGEE_VERSION macro
 * is set on compile time. See Makefile for details.
 */
const char * get_version() {
    return CEEGEE_VERSION;
}
