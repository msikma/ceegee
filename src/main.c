/*
 * Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>

#include "utils/run.h"
#include "utils/args.h"
#include "test/vga_test.h"

/**
 * Main program.
 */
int main(int argc, const char **argv)
{
    startup_proc();

    // Check if any command-line arguments were passed
    // and run the appropriate function.
    int cmd = handle_command_line_args(argc, argv);
    switch (cmd) {
        case ARG_RUN_TEST:
            run_vga_test();
            break;
        default:
            printf("starting game...\r\n");
            break;
    }

    shutdown_proc();
    return 0;
}
