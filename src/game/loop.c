/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/game.h"
#include "src/game/handlers/flying.h"
#include "src/game/handlers/initial.h"
#include "src/game/handlers/logos.h"
#include "src/game/state.h"

// Whether the game loop will exit.
bool game_loop_exit = FALSE;
// Whether the current handler will exit.
bool handler_exit = FALSE;

// Pointers to the active handler functions.
void (*handler_init_ptr)();
void (*handler_update_ptr)();
void (*handler_render_ptr)();
bool (*handler_will_exit_ptr)();
void (*handler_exit_ptr)();

/**
 * Sets the current handler by setting our pointers to its functions.
 */
void set_handler() {
    switch (get_curr_state()) {
        // Initial state: performs all tasks that are globally required
        // for the game to function, and loads all basic resources.
        case STATE_INITIAL:
            handler_init_ptr = initial_init;
            handler_update_ptr = initial_update;
            handler_render_ptr = initial_render;
            handler_will_exit_ptr = initial_will_exit;
            handler_exit_ptr = initial_exit;
            break;
        // Displays the logos at the start of the game.
        case STATE_LOGOS:
            handler_init_ptr = logos_init;
            handler_update_ptr = logos_update;
            handler_render_ptr = logos_render;
            handler_will_exit_ptr = logos_will_exit;
            handler_exit_ptr = logos_exit;
            break;
        // When flying a spaceship in a level.
        case STATE_FLYING:
            handler_init_ptr = flying_init;
            handler_update_ptr = flying_update;
            handler_render_ptr = flying_render;
            handler_will_exit_ptr = flying_will_exit;
            handler_exit_ptr = flying_exit;
            break;
        default:
            // We've entered an unknown state.
            // TODO: error handler.
            break;
    }
}

/**
 * Returns whether or not the game loop should exit.
 */
bool game_loop_will_exit() {
    if (get_curr_state() == STATE_EXIT) {
        return true;
    }
    return false;
}

/**
 * Game loop function.
 *
 * The game loop is responsible for overseeing the main game logic.
 * It doesn't handle any game logic or change any of the game's state,
 * but it is responsible for calling the parts of the code that do.
 *
 * The game has an internal primary state, and based on that state
 * we hook onto a 'handler' and then call the handler's functions.
 * Each handler has several predetermined external functions:
 *
 *    - init()      - Ensures that it has all resources loaded to work.
 *    - update()    - Updates the internal state based on user input and logic.
 *    - render()    - Renders its output to a bitmap buffer.
 *    - will_exit() - Returns true if we must stop this handler.
 *    - exit()      - Shuts down the handler and unloads resources.
 *
 * Each handler has only these functions externally callable.
 *
 * To begin with, we check what the current game state is.
 * Based on the state, we'll set five function pointers to the functions
 * provided by the appropriate handler. So if the user has just started
 * a level, we would set the function pointers to 'level_init', etc.
 *
 * This takes place in the outer loop. Once the handler is set, we call
 * its init() function and enter the inner loop, which executes once
 * per frame and calls the handler's update() and render() functions.
 *
 * When a handler is done (for example, if a user has completed a level,
 * and control of the game logic must be handed back to the 'menu' handler)
 * its will_exit() function will return true. At that point, the inner loop
 * is broken and we go back into the outer loop, where a new handler is chosen.
 *
 * When exiting the outer game loop, the game itself is shut down.
 */
void game_loop() {
    while (!game_loop_exit) {
        // Determine which handler to use. This sets all variables
        // ending in _ptr to the appropriate handler functions.
        set_handler();

        // Ask the handler to initialize itself.
        handler_init_ptr();

        // Start the handler's own loop. Run update(), vsync() and render(),
        // until the handler asks to be terminated.
        handler_exit = false;
        while (!handler_exit) {
            handler_update_ptr();
            vsync();
            handler_render_ptr(screen);
            handler_exit = handler_will_exit_ptr();
        }

        // Ask the handler to shut itself down and deallocate any
        // resources we don't need anymore.
        handler_exit_ptr();

        // Advance to the next game state.
        advance_state();

        // Check whether we need to exit the outer game loop, too.
        // This is true when we're shutting down the game.
        game_loop_exit = game_loop_will_exit();
    }

    // Since the game loop has been exited, shut down the game
    // and return to the OS.
    shutdown();
}
