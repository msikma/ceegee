/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_UTILS_ARGS__
#define __CEEGEE_UTILS_ARGS__

#define ARG_NOTHING 1
#define ARG_VERSION 2
#define ARG_JUKEBOX 3
#define ARG_USAGE 4
#define ARG_SYSINFO 5

int parse_args(int argc, char **argv);
void print_usage();

#endif
