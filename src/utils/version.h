/*
 * Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */

#ifndef __CEEGEE_VERSION__
#define __CEEGEE_VERSION__

const char *get_copyright();
const char *get_name();
const char *get_short_version();
const char *get_url();
const char *get_version();
const char *get_cc_info();
const char *get_os_info();
const char *get_cflags();
const char *get_ldflags();
const char *get_build_time();
void print_version();

#endif
