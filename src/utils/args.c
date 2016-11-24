/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "src/utils/args.h"
#include "src/utils/version.h"

/**
 * Prints the program's usage information, MS-DOS style.
 */
void print_usage(char *name) {
    printf("%s, %s\r\n", get_name(), get_copyright());
    printf("\r\n");
    printf("Usage: %s [options]\r\n", name);
    printf("\r\n");
    printf("  /h or /?  Display usage information.\r\n");
    printf("  /v        Display version.\r\n");
    printf("  /b        Write build information for debugging.\r\n");
    printf("  /j        Play a song from the jukebox.\r\n");
    printf("\r\n");
    printf("More information: %s\r\n", get_url());
}

/**
 * Parses command-line arguments and returns one of the ARG_* macros.
 * MS-DOS style slash arguments are accepted. We're not using getopt()
 * because it only seems to support dash arguments.
 */
int parse_args(int argc, char **argv) {
    if (argc <= 1) {
        return ARG_NOTHING;
    }

    // Skip over the program name.
    for (int a = 1; a < argc; ++a) {
        if (strcmp(argv[a], "/?") == 0) {
            return ARG_USAGE;
        }
        if (strcmp(argv[a], "/h") == 0 || strcmp(argv[a], "/H") == 0) {
            return ARG_USAGE;
        }
        if (strcmp(argv[a], "/v") == 0 || strcmp(argv[a], "/V") == 0) {
            return ARG_VERSION;
        }
        if (strcmp(argv[a], "/b") == 0 || strcmp(argv[a], "/B") == 0) {
            return ARG_SYSINFO;
        }
        if (strcmp(argv[a], "/j") == 0 || strcmp(argv[a], "/J") == 0) {
            return ARG_JUKEBOX;
        }
    }

    return ARG_NOTHING;
}
