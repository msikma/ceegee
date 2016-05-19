/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_UTILS_ARGS__
#define __CEEGEE_UTILS_ARGS__

#define ARG_NOTHING 1
#define ARG_RUN_TEST 2
#define ARG_JUKEBOX 3

static char *filename(char *path);
int handle_args(int argc, const char **argv);
int parse_args(int argc, const char **argv);

#endif
