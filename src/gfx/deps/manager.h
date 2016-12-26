/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <allegro.h>

#ifndef __CEEGEE_GFX_DEPS_MANAGER__
#define __CEEGEE_GFX_DEPS_MANAGER__

// Maximum number of objects that can claim to own a resource.
#define RES_OWNERS_MAX 100
// Maximum size of a resource path.
#define RES_PATH_MAX 50

// CGRES (CeeGee resource) object.
typedef struct CGRES {
    int id;
    int own_count;
    int owners[RES_OWNERS_MAX];
    char path[RES_PATH_MAX];
    int p_extra;
    DATAFILE *data;
} CGRES;


DATAFILE *dep_data_ref(int res);
static CGRES *init_cgres(int id, char *path);
void debug_res_list();
void debug_res(CGRES *item);
void dep_forget(int res, int req);
void dep_require(int res, int req);
void res_register(int res, char path[], void (*cb)());

#endif
