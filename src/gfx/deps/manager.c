/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "src/gfx/deps/manager.h"

// List of actively loaded resources.
int active_res[1000];
// List of resources we want to load.
int load_res[1000];
// List of resources we no longer need.
int unload_res[1000];
// List of resources that can be requested.
CGRES* res_list[1000];
// Callback functions.
void (*res_cb[1000])();

/**
 * Prints out a list of all resources for debugging.
 */
void debug_res_list() {
    printf("Resource list:\n\n");
    for (int a = 0; a < 1000; ++a) {
        if (res_list[a]) {
            printf("%03d: ", a);
            debug_res(res_list[a]);
        }
    }
}

/**
 * Prints a description of a single resource for debugging.
 */
void debug_res(CGRES *item) {
    int a;
    bool lstart = FALSE;

    printf(
        "<CGRES (%s) id=%d path=\"%s\" own_count=%d owners={",
        item->data ? "loaded" : "unloaded",
        item->id,
        item->path,
        item->own_count
    );
    for (a = 0; a < RES_OWNERS_MAX; ++a) {
        if (item->owners[a] != -1) {
            if (lstart) {
                printf(",");
            }
            printf("%i", item->owners[a]);
            lstart = TRUE;
        }
    }
    printf("}>\n");
}

/**
 * Initializes and returns a new CGRES object.
 */
static CGRES *init_cgres(int id, char *path) {
    CGRES *item = malloc(sizeof(CGRES));
    item->id = id;
    item->own_count = 0;
    item->data = 0;
    strcpy(item->path, path);
    memset(item->owners, 0xFF, RES_OWNERS_MAX * sizeof(int));
    return item;
}

/**
 * Returns a reference to a loaded datafile. Used to access the data
 * previously loaded by dependency management.
 */
DATAFILE *dep_data_ref(int res) {
    return res_list[res]->data;
}

/**
 * Loads a dependency for a specific piece of code.
 *
 * Two arguments are required: the ID of the resource that is being requested,
 * and an identifier for the piece of code that needs the resource.
 *
 * For example, if I write a game handler that requires a sprite of
 * a USP Talon ship, I might ask for RES_SPRITE_USP_TALON to be loaded
 * for the REQ_HANDLER_FLYING id. The name is later reused when indicating that
 * the handler is being removed from memory and no longer needs the resource.
 *
 * It's strongly recommended to use only #define aliases for this function
 * to avoid accidentally using the wrong string, which would cause
 * a memory leak.
 *
 * In most cases, this is used in low level objects, such as a sprite struct.
 */
void dep_require(int res, int req) {
    int a;
    int *own_count = &res_list[res]->own_count;

    // Check if this req is already registered as requiring this resource.
    for (a = 0; a < *own_count; ++a) {
        if (res_list[res]->owners[a] == req) {
            // No need to do anything.
            return;
        }
    }

    // The owners array always has a free spot at $own_count.
    res_list[res]->owners[*own_count] = req;
    *own_count += 1;

    // Load the resource file and call its callback function.
    res_list[res]->data = load_datafile(res_list[res]->path);
    if (*res_cb[res] != 0) {
        (*res_cb[res])();
    }
}

/**
 * Indicates that a resource is no longer needed.
 *
 * This does not necessarily unload the resource. It simply indicates
 * that a particular piece of code no longer needs the resource.
 * If nobody needs a resource anymore, the resource is unloaded.
 */
void dep_forget(int res, int req) {
    int a, n = 0;
    int own_sz = RES_OWNERS_MAX * sizeof(int);
    int owners[RES_OWNERS_MAX];
    int *own_count = &res_list[res]->own_count;

    // Unload the datafile. If anyone is still using it
    // after this, the game will crash.
    unload_datafile(res_list[res]->data);
    res_list[res]->data = NULL;

    // Remove the requester from the list of resource owners.
    // We'll do this by rebuilding the array so that there are no gaps.
    memset(owners, 0xFF, own_sz);

    // Copy all except req from the original list.
    for (a = 0; a < *own_count; ++a) {
        if (res_list[res]->owners[a] != req) {
            owners[n] = res_list[res]->owners[a];
            n+= 1;
        }
    }

    // Copy the new list to the resource and update its owners count.
    memcpy(res_list[res]->owners, owners, own_sz);
    *own_count = n;
}

/**
 * Registers a resource. After it has been registered, it can be requested
 * by anything. All resources are registered all at once during
 * program startup. See <init.c> for more information.
 */
void res_register(int res, char path[], void (*cb)()) {
    CGRES *resource = init_cgres(res, path);
    res_list[res] = resource;

    // Store our callback function if we have one.
    res_cb[res] = cb;
}
