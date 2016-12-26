/*
 * Copyright (C) 2015-2017, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "src/utils/build.h"
#include "src/utils/version.h"

char sysinfo[1024] = "";
bool has_info = false;

/**
 * Formats system information. Here is an example:
 *
 * CeeGee Engine, (C) 2015-2017, Michiel Sikma (MIT license)
 *
 * TIME=2016-11-24T13:32:40+0100
 * BUILD=103-MASTER 2016-11-24 (DD160F4)
 * CC=i586-pc-msdosdjgpp-gcc (GCC) 5.2.0
 * OS=Darwin Kernel Version 16.1.0: Thu Oct 13 21:26:57 PDT 2016;
 * root:xnu-3789.21.3~60/RELEASE_X86_64
 * CFLAGS=-DHAVE_STDBOOL_H=1 -DALLEGRO_HAVE_INTTYPES_H -fgnu89-inline -Wall
 * -Wno-unused -O3 -mtune=i586 -ffast-math -fomit-frame-pointer
 * -Ivendor/allegro-4.2.2-xc/include -Ivendor/xorshift -I. -DDEBUG=1
 * LDFLAGS=-Lvendor/allegro-4.2.2-xc/lib/djgpp -lalleg
 */
static void format_sysinfo() {
  if (has_info) {
    return;
  }

  // Format all system information into one string.
  snprintf(
    sysinfo,
    sizeof(sysinfo),
    "%s, %s\n\n"
    "TIME=%s\n"
    "BUILD=%s\n"
    "CC=%s\n"
    "OS=%s\n"
    "CFLAGS=%s\n"
    "LDFLAGS=%s\n",
    get_name(),
    get_copyright(),
    get_build_time(),
    get_short_version(),
    get_cc_info(),
    get_os_info(),
    get_cflags(),
    get_ldflags()
  );
}

/**
 * Prints the system information.
 */
void print_sysinfo() {
  format_sysinfo();
  printf(sysinfo);
}

/**
 * Writes system info to a file for debugging purposes.
 */
int write_sysinfo(char fn[]) {
  format_sysinfo();

  FILE *dbgfile = fopen(fn, "w");
  if (dbgfile == NULL) {
    return SYSINFO_ERROR_OPENING_FILE;
  }
  fprintf(dbgfile, sysinfo);
  fclose(dbgfile);
  return SYSINFO_SUCCESS;
}

/**
 * Writes a file with debugging info to 'dbginfo.txt',
 * and provides feedback to the user after failure or success.
 */
int write_sysinfo_fb() {
  char fn[] = "dbginfo.txt";
  int status = write_sysinfo(fn);
  if (status == SYSINFO_ERROR_OPENING_FILE) {
    printf("\r\nError: couldn't open %s for writing.", fn);
  }
  if (status == SYSINFO_SUCCESS) {
    printf("\r\nWrote system information to %s.", fn);
  }
  return status;
}
