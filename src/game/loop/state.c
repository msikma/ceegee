/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "src/game/loop/state.h"

// Active game state.
int curr_state = STATE_INITIAL;
// Future state that we intend to transition to after the active state.
int next_state = STATE_INITIAL;

/**
 * Sets the active game state.
 */
void set_curr_state(int state) {
  curr_state = state;
}

/**
 * Returns the active game state.
 */
int get_curr_state() {
  return curr_state;
}

/**
 * Sets the future game state, following the active state.
 *
 * Sets the game state we will be in once the current game handler
 * finishes its work. For example, if we're currently in a menu,
 * that menu might either request an in-game state, or a game exit state,
 * depending on what option was chosen. We'll save that next state here,
 * and transition the active state to it once we're ready.
 */
void set_next_state(int state) {
    next_state = state;
}

/**
 * Returns the future game state.
 */
int get_next_state() {
    return next_state;
}

/**
 * Advances to the next state. This is called after each game loop handler
 * finishes its work and shuts down.
 */
void advance_state() {
    set_curr_state(get_next_state());
    set_next_state(STATE_UNDETERMINED);
}
