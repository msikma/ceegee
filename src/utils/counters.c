/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include "src/utils/counters.h"

int counter_req_id = 0;
int counter_res_id = 0;

/**
 * Returns the next global ID for requesters.
 */
int req_id() {
    return counter_req_id++;
}

/**
 * Returns the next global ID for resources.
 */
int res_id() {
    return counter_res_id++;
}
