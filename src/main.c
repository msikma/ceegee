/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>

#include "utils/args.h"
#include "game.h"
#include "midi.h"
#include "version.h"

/**
 * Main entrance point of the application.
 */
int main(int argc, const char **argv) {
    // Check command line arguments and run commands if necessary.
    // If no arguments were entered, the main program proceeds as normal.
    int cmd = handle_args(argc, argv);

    switch (cmd) {
        case ARG_VERSION:
            printf("%s", get_version());
            return 0;
    }

    // Run the main game code.
    start_game();

    return 0;
}
