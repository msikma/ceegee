/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>

#include "src/audio/midi.h"
#include "src/game.h"
#include "src/jukebox.h"
#include "src/utils/args.h"
#include "src/utils/version.h"
#include "src/utils/build.h"

/**
 * Main entrance point of the application.
 */
int main(int argc, char **argv) {
    // Check command line arguments and run commands if necessary.
    // If no arguments were entered, the main program proceeds as normal.
    int cmd = parse_args(argc, argv);

    switch (cmd) {
        case ARG_USAGE:
            print_usage(basename(argv[0]));
            return 0;
        case ARG_VERSION:
            print_version();
            return 0;
        case ARG_SYSINFO:
            print_sysinfo();
            return write_sysinfo_fb();
        case ARG_JUKEBOX:
            start_jukebox();
            return 0;
    }

    // Run the main game code.
    start_game();

    return 0;
}
