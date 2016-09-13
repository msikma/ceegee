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

void print_usage(char *name) {
    printf("%s, %s\r\n", get_name(), get_copyright());
    printf("\r\n");
    printf("Usage: %s [options]\r\n", name);
    printf("\r\n");
    printf("  /h /?     Display usage information and exit.\r\n");
    printf("  /v        Display version and exit.\r\n");
    printf("  /j        Play a song from the jukebox.\r\n");
    printf("\r\n");
    printf("More information: %s\r\n", get_url());
}

int parse_args(int argc, char **argv) {
    if (argc <= 1) {
        return ARG_NOTHING;
    }

    for (int a = 1; a < argc; ++a) {
        if (strcmp(argv[a], "/?") == 0) {
            return ARG_USAGE;
        }
        if (strcmp(argv[a], "/h") == 0) {
            return ARG_USAGE;
        }
        if (strcmp(argv[a], "/v") == 0) {
            return ARG_VERSION;
        }
        if (strcmp(argv[a], "/j") == 0) {
            return ARG_JUKEBOX;
        }
    }

    return ARG_NOTHING;
}
