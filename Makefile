# Copyright (C) 2015-2016, Michiel Sikma <michiel@sikma.org>
# MIT license

CC        = ${DJGPP_CC}
VENDOR    = vendor
CFLAGS    = -DHAVE_STDBOOL_H=1 -DALLEGRO_HAVE_INTTYPES_H -fgnu89-inline -Ivendor/allegro-4.2.2-xc/include -Ivendor/xorshift -I.
LDFLAGS   = -Lvendor/allegro-4.2.2-xc/lib/djgpp -lalleg

TITLE     = CeeGee Engine
COPYRIGHT = (C) 2015-2016, Michiel Sikma (MIT license)
URL       = https://github.com/msikma/ceegee

BIN       = ceegee.exe
SRCDIR    = src
OBJDIR    = obj
DISTDIR   = dist
STATICDIR = static
RESDIR    = resources
RESHDIR   = src/gfx/res/data

# All resource files that are to be generated,
# and all their corresponding header files.
RESDATS  = ${STATICDIR}/data/font/flim.dat
RESDDEST = $(subst ${STATICDIR},${DISTDIR},${RESDATS})
RESHS    = ${RESHDIR}/flim_data.h

# Static files, e.g. the readme.txt file, that get copied straight to
# the dist directory.
STATIC    = $(shell find ${STATICDIR} -name "*.*" -not -name ".*" 2> /dev/null)
STATICDEST= $(subst ${STATICDIR},${DISTDIR},${STATIC}) ${RESDDEST}

# All source files (*.c) and their corresponding object files.
SRC       = $(shell find ${SRCDIR} -name "*.c" 2> /dev/null) \
            $(shell find ${VENDOR}/xorshift -name "*.c" -not -name "test_*.c" 2> /dev/null)
OBJS      = $(SRC:%.c=%.o)

# Some information from Git that we'll use for the version indicator file.
HASH      = $(shell git rev-parse --short HEAD | awk '{print toupper($0)}')
BRANCH    = $(shell git describe --all | sed s@heads/@@ | awk "{print toupper($0)}")
COUNT     = $(shell git rev-list HEAD --count)
DATE      = $(shell date +"%Y-%m-%d %T")
VDEF      = -DCEEGEE_NAME="\"${TITLE}\"" -DCEEGEE_URL="\"${URL}\"" -DCEEGEE_COPYRIGHT="\"${COPYRIGHT}\"" -DCEEGEE_VERSION="\"${TITLE}\r\nBuild: ${COUNT}-${BRANCH} ${DATE} (${HASH})\r\n\""

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

.PHONY: clean version static
default: all

${DISTDIR}:
	mkdir -p ${DISTDIR}

%.o: %.c
	${CC} -c -o $@ $? ${CFLAGS}

# Pass on the version string to the version.c file.
src/utils/version.o: src/utils/version.c
	${CC} -c -o $@ $? ${CFLAGS} ${VDEF}

${DISTDIR}/${BIN}: ${OBJS}
	${CC} -o ${DISTDIR}/${BIN} $+ ${LDFLAGS}

${STATICDEST}: ${DISTDIR}
	@mkdir -p $(shell dirname $@)
	cp $(subst ${DISTDIR},${STATICDIR},$@) $@

all: ${DISTDIR} ${RESHS} version ${DISTDIR}/${BIN} ${STATICDEST}

static: ${STATICDEST}

clean:
	rm -rf ${DISTDIR}
	rm -f ${OBJS} ${RESHS} ${RESDATS}

# From here on is a list of all resource files created by the dat utility.
# All items here should also appear in the ${RESDATS} and ${RESHS} variables.

${STATICDIR}/data/font/flim.dat:
	dat $@ -c2 -f -bpp 8 -t font -n1 -a ${RESDIR}/font/flim_w.pcx ${RESDIR}/font/flim_g.pcx -s0

${RESHDIR}/flim_data.h: ${STATICDIR}/data/font/flim.dat
	dat ${STATICDIR}/data/font/flim.dat -h $@
