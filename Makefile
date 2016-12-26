# Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
# MIT license

# Ensure that Bash is used for Makefile recipes.
SHELL     = /usr/bin/env bash

CC        = ${DJGPP_CC}
VENDOR    = vendor
CFLAGS    = -DHAVE_STDBOOL_H=1 -DALLEGRO_HAVE_INTTYPES_H -fgnu89-inline -Wall -Wno-unused -O3 -mtune=i586 -ffast-math -fomit-frame-pointer -Ivendor/allegro-4.2.2-xc/include -Ivendor/xorshift -I.
LDFLAGS   = -Lvendor/allegro-4.2.2-xc/lib/djgpp -lalleg

# Enable debugging functionality if invoked with DEBUG=1.
# We'll also add _debug as a suffix to all object files with _debug
# and rename the exe file, to force the game to be recompiled completely
# if debugging is enabled.
ifdef DEBUG
	CFLAGS += -DDEBUG=1
	OBJSFX  = _debug
	EXENAME = cgdebug
else
	CFLAGS += -DDEBUG=0
	OBJSFX  =
	EXENAME = ceegee
endif

TITLE     = CeeGee Engine
COPYRIGHT = (C) 2015-2016, Michiel Sikma (MIT license)
URL       = https://github.com/msikma/ceegee

BIN       = ${EXENAME}.exe
SRCDIR    = src
DISTDIR   = dist/ceegee
STATICDIR = static
RESDIR    = resources
RESHDIR   = ${SRCDIR}/gfx/res/data

# All resource files that are to be generated,
# and all their corresponding header files.
STATICRES= ${STATICDIR}/data/res
RESDATS  = ${STATICRES}/font/flim.dat ${STATICRES}/font/tin.dat ${STATICRES}/logos.dat ${STATICRES}/usptalon.dat
RESDDEST = $(subst ${STATICDIR},${DISTDIR},${RESDATS})
RESHS    = ${RESHDIR}/flim_data.h ${RESHDIR}/tin_data.h ${RESHDIR}/logos_data.h ${RESHDIR}/usp_talon_data.h

# Static files, e.g. the readme.txt file, that get copied straight to
# the dist directory. We're not including the ${STATICRES} directory
# because those files are generated: so if they were already generated before,
# we'd get a duplicate rule error. These files are appended to ${STATICDEST}.
STATIC    = $(shell find ${STATICDIR} -name "*.*" -not -name ".*" -type f ! -path ${STATICRES}?* 2> /dev/null)
STATICDEST= $(subst ${STATICDIR},${DISTDIR},${STATIC}) ${RESDDEST}

# All source files (*.c) and their corresponding object files.
SRC       = $(shell find ${SRCDIR} -name "*.c" 2> /dev/null) \
            $(shell find ${VENDOR}/xorshift -name "*.c" -not -name "test_*.c" 2> /dev/null)
OBJS      = $(SRC:%.c=%${OBJSFX}.o)
# All object files, including those for .c files that no longer exist.
# Used to ensure we delete all object files.
ALL_OBJS  = $(shell find ${SRCDIR} -name "*.o" 2> /dev/null) \
            $(shell find ${VENDOR}/xorshift -name "*.o" -not -name "test_*.o" 2> /dev/null)

# Some information from Git that we'll use for the version indicator file.
# TODO: it works, but we should probably escape the quotes in these variables.
HASH      = $(shell git rev-parse --short HEAD | tr [:lower:] [:upper:])
BRANCH_LC = $(shell git describe --all | sed s@heads/@@)
BRANCH    = $(shell echo ${BRANCH_LC} | tr [:lower:] [:upper:])
COUNT     = $(shell git rev-list HEAD --count)
DATE      = $(shell date +"%Y-%m-%d")
DATETIME  = $(shell date +"%Y-%m-%d %T")
OSINFO    = $(shell uname -v)
BUILDTIME = $(shell date +"%Y-%m-%dT%T%z")
CCINFO    = $(shell ${DJGPP_CC} --version | head -n 1)
VDEF      = -DCEEGEE_NAME="\"${TITLE}\"" -DCEEGEE_URL="\"${URL}\"" -DCEEGEE_COPYRIGHT="\"${COPYRIGHT}\"" -DCEEGEE_VERSION="\"${TITLE}\r\nBuild ${COUNT}-${BRANCH} ${DATETIME} (${HASH})\r\n\"" -DCEEGEE_SHORT_VERSION="\"${COUNT}-${BRANCH} ${DATE} (${HASH})\"" -DCEEGEE_OSINFO="\"${OSINFO}\"" -DCEEGEE_CCINFO="\"${CCINFO}\"" -DCEEGEE_CFLAGS="\"${CFLAGS}\"" -DCEEGEE_LDFLAGS="\"${LDFLAGS}\"" -DCEEGEE_BUILDTIME="\"${BUILDTIME}\""

# When making a zip file, we don't want to include the dist/ directory.
# Set additional variables here. The ZIPLOCAL file is used after we pushd
# to dist/.
DISTPUSHD = dist
ZIPDIST   = dist/ceegee.zip
ZIPFILES  = ceegee
ZIPOPTS   = -r -9 -T -o -v

# Include only the debugging exe by default, and vice versa.
ifdef DEBUG
	ZIPLOCAL = ceegee-${BRANCH_LC}-debug-${COUNT}.zip
	ZIPEXCL = --exclude=*ceegee.exe*
else
	ZIPLOCAL = ceegee-${BRANCH_LC}-${COUNT}.zip
	ZIPEXCL = --exclude=*cgdebug.exe*
endif

# Check if a DJGPP compiler exists.
ifndef DJGPP_CC
  $(error To compile Ceegee, you need to set the DJGPP_CC environment variable to a DJGPP GCC binary, e.g. /usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc)
endif

# Check if Allegro has been compiled correctly.
ifeq ("$(wildcard vendor/allegro-4.2.2-xc/lib/djgpp/liballeg.a)","")
  $(error To compile Ceegee, you need to compile Allegro first. Check the instructions in the readme)
endif

# Check if the dat utility is available.
ifeq (, $(shell which dat))
  $(error To compile Ceegee, the Allegro dat utility is required and must be on the path)
endif

.PHONY: clean static res
default: game

${DISTDIR}:
	mkdir -p ${DISTDIR}

${RESHDIR}:
	mkdir -p ${RESHDIR}

${STATICRES}/font/:
	mkdir -p ${STATICRES}/font/

%${OBJSFX}.o: %.c
	${CC} -c -o $@ $? ${CFLAGS}

# Pass on the version string to the version.c file.
src/utils/version${OBJSFX}.o: src/utils/version.c
	${CC} -c -o $@ $? ${CFLAGS} ${VDEF}

${DISTDIR}/${BIN}: ${OBJS}
	${CC} -o ${DISTDIR}/${BIN} $+ ${LDFLAGS}

${STATICDEST}: ${DISTDIR}
	@mkdir -p $(shell dirname $@)
	cp $(subst ${DISTDIR},${STATICDIR},$@) $@

${ZIPDIST}: game
	pushd ${DISTPUSHD}; \
	zip ${ZIPOPTS} ${ZIPLOCAL} ${ZIPFILES} ${ZIPEXCL};

dist: ${ZIPDIST}

all: game ${ZIPDIST}

game: ${DISTDIR} ${RESHDIR} ${STATICRES}/font/ ${RESHS} ${DISTDIR}/${BIN} ${STATICDEST}

static: ${STATICDEST}

res: ${RESHS}

clean:
	rm -rf ${DISTDIR}
	rm -f ${DISTPUSHD}/ceegee-*.zip
	rm -f ${ALL_OBJS}
	rm -f ${RESHS} ${RESDATS}
	rm -rf ${STATICRES}/font/ ${RESHDIR}

# From here on is a list of all resource files created by the dat utility.
# All items here should also appear in the ${RESDATS} and ${RESHS} variables.
#
# A quick run-down of the common options we use:
#
#     -a        - adds an object to the datafile
#     -bpp 8    - use 8-bit colors
#     -c1       - compress individually (usually recommended)
#     -c2       - compress globally
#     -f        - store relative filename references instead of absolute
#     -k        - keep original filename as reference (we then rename it)
#     -n1       - sort alphabetically
#     -s0       - don't strip any meta information from the file
#     -t <TYPE> - treat as a particular object type (e.g. BMP, XCMP, FONT)

${STATICRES}/logos.dat:
	dat $@ -c1 -f -bpp 8 -t BMP -n1 -k -s0 -a ${RESDIR}/logos/aslogo.pcx ${RESDIR}/logos/test.pcx
	dat $@ aslogo.pcx NAME=ASLOGO_IMG
	dat $@ test.pcx NAME=TEST_IMG
	dat $@ -c1 -f -bpp 8 -t PAL -n1 -k -s0 -a ${RESDIR}/logos/aslogo.pcx ${RESDIR}/logos/test.pcx
	dat $@ aslogo.pcx NAME=ASLOGO_PALETTE
	dat $@ test.pcx NAME=TEST_PALETTE

${RESHDIR}/logos_data.h: ${STATICRES}/logos.dat
	dat ${STATICRES}/logos.dat -h $@

${STATICRES}/usptalon.dat:
	dat $@ -c1 -f -bpp 8 -t CMP -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_m.pcx
	dat $@ usp_talon_m.pcx NAME=USP_TALON_M
	dat $@ -c1 -f -bpp 8 -t CMP -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_l1.pcx
	dat $@ usp_talon_l1.pcx NAME=USP_TALON_L1
	dat $@ -c1 -f -bpp 8 -t CMP -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_l2.pcx
	dat $@ usp_talon_l2.pcx NAME=USP_TALON_L2
	dat $@ -c1 -f -bpp 8 -t CMP -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_r1.pcx
	dat $@ usp_talon_r1.pcx NAME=USP_TALON_R1
	dat $@ -c1 -f -bpp 8 -t CMP -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_r2.pcx
	dat $@ usp_talon_r2.pcx NAME=USP_TALON_R2
	dat $@ -c1 -f -bpp 8 -t PAL -n1 -k -s0 -a ${RESDIR}/sprites/usp_talon_m.pcx
	dat $@ usp_talon_m.pcx NAME=USP_TALON_PALETTE

${RESHDIR}/usp_talon_data.h: ${STATICRES}/usptalon.dat
	dat ${STATICRES}/usptalon.dat -h $@

${STATICRES}/font/flim.dat:
	dat $@ -c2 -f -bpp 8 -t FONT -n1 -k -s0 -a ${RESDIR}/font/flim_w.pcx ${RESDIR}/font/flim_g.pcx
	dat $@ flim_w.pcx NAME=FLIM_WHITE
	dat $@ flim_g.pcx NAME=FLIM_GRAY

${RESHDIR}/flim_data.h: ${STATICRES}/font/flim.dat
	dat ${STATICRES}/font/flim.dat -h $@

${STATICRES}/font/tin.dat:
	dat $@ -c2 -f -bpp 8 -t FONT -n1 -k -s0 -a ${RESDIR}/font/tin_w.pcx ${RESDIR}/font/tin_g.pcx
	dat $@ tin_w.pcx NAME=TIN_WHITE
	dat $@ tin_g.pcx NAME=TIN_GRAY

${RESHDIR}/tin_data.h: ${STATICRES}/font/tin.dat
	dat ${STATICRES}/font/tin.dat -h $@
