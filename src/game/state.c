/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stddef.h>

#include "src/game/state.h"

// Primary game state object.
game_state_obj game_state;

void initialize_game_state() {
    game_state_obj game_state = {
        // Which loop state to transition into after initial setup.
        .loop_state_post_init = NULL
    };
}
