/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>
#include <string.h>
#include <argparse.h>

#include "src/utils/args.h"

/**
 * Retrieves the current filename. In DOS, argv[0] contains a path.
 * We strip out everything except the actual filename.
 * Currently unused. TODO: use this.
 */
static char *filename(char *path)
{
    const char name[255];
    const char delims[] = "/\\";
    char *token, *last;

    assert(path != NULL);
    if (strlen(path) >= sizeof(name)) {
        // Somehow the path was longer than MSDOS would normally permit.
        return "main.exe";
    }

    while ((token = strsep(&path, delims)) != NULL) {
        last = token;
    }
    return last;
}

int parse_args(int argc, const char **argv)
{
    // Help and description text.
    static const char *const usage[] = {
        "ceegee.exe [options] [[--] args]",
        NULL,
    };
    char* info_footer = "\nInternet users find our latest software at:\nhttps://github.com/msikma/ceegee";

    // The flags we'll check for.
    int test = 0;
    int juke = 0;

    // Build the argparse object itself.
    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_GROUP("Basic options"),
        OPT_HELP(),
        OPT_BOOLEAN('v', "version", &test, "display version and exit"),
        OPT_BOOLEAN('j', "jukebox", &juke, "play a song from the jukebox"),
        OPT_END(),
    };

    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, NULL, info_footer);
    argc = argparse_parse(&argparse, argc, argv);

    if (test != 0) {
        return ARG_VERSION;
    }
    if (juke != 0) {
        return ARG_JUKEBOX;
    }
    return ARG_NOTHING;
}

/**
 * Handles the command line arguments.
 */
int handle_args(int argc, const char **argv)
{
    if (argc <= 1) {
        return ARG_NOTHING;
    }
    return parse_args(argc, argv);
}
