/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

// Datafile indices for monoreg.dat.
#define MONOREG_COLOR 0
#define MONOREG_GRAY 1
#define MONOREG_PALETTE 2
#define MONOREG_WHITE 3

extern DATAFILE *MONOREG;
extern int MONOREG_HEIGHT;

int load_monoreg();
int unload_monoreg();
