/*
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>
#include <string.h>

#include "args.h"
#include "../../vendor/argparse/argparse.h"

/**
 * Retrieves the current filename. In DOS, argv[0] contains a path.
 * We strip out everything except the actual filename.
 * Currently unused.
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
    char* info_header = "\nAdd header text here.";
    char* info_footer = "\nAdd footer text here.";

    // The flags we'll check for.
    int test = 0;

    // Build the argparse object itself.
    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_GROUP("Basic options"),
        OPT_HELP(),
        OPT_BOOLEAN('t', "test", &test, "runs a series of tests"),
        OPT_END(),
    };

    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, info_header, info_footer);
    argc = argparse_parse(&argparse, argc, argv);

    if (test != 0) {
        return ARG_RUN_TEST;
    }
    return ARG_NOTHING;
}

/**
 * Handles the command line arguments.
 */
int handle_command_line_args(int argc, const char **argv)
{
    if (argc <= 1) {
        return ARG_NOTHING;
    }
    return parse_args(argc, argv);
}
