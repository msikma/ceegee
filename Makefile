# Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
# MIT License

CC        = $(DJGPP_CC)
VENDOR    = vendor
CFLAGS    =
LDFLAGS   =

TITLE     = CeeGee Engine
BIN       = ceegee.exe
SRCDIR    = src
OBJDIR    = obj
DISTDIR   = dist
STATICDIR = src/static

# Static files, e.g. the readme.txt file, that get copied straight to
# the dist directory.
STATIC    = $(shell find $(STATICDIR) -name "*.*")
STATICDEST= $(subst $(STATICDIR),$(DISTDIR),$(STATIC))

# All source files (*.c) and their corresponding object files.
SOURCES   = $(shell find $(SRCDIR) -name "*.c") $(shell find $(VENDOR) -name "*.c" -not -path "$(VENDOR)/allegro/*" -not -name "test_*.c")
OBJS      = $(SOURCES:%.c=%.o)

# Some information from Git that we'll use for the version indicator file.
HASH      = $(shell git rev-parse HEAD)
BRANCH    = $(shell git describe --all | sed s@heads/@@ | awk '{print toupper($0)}')
COUNT     = $(shell git rev-list HEAD --count)
DATE      = $(shell date +'%Y-%m-%d %T')

.PHONY: clean dir version
default: all

dir:
	@mkdir -p ${DISTDIR}

version:
	@echo "${TITLE}\nBuild: ${COUNT}-${BRANCH} ${DATE}\nHash: ${HASH}" > ${DISTDIR}/version.txt

%.o: %.c
	${CC} -c -o $@ $? ${CFLAGS}

${DISTDIR}/${BIN}: ${OBJS}
	${CC} -o ${DISTDIR}/${BIN} $+ ${LDFLAGS}

${STATICDEST}: ${STATIC}
	cp $< $@

all: dir version ${DISTDIR}/${BIN} ${STATICDEST}

clean:
	rm -rf ${DISTDIR}
	rm -f ${OBJS}
