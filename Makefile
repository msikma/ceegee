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

SOURCES   = $(shell find $(SRCDIR) -name "*.c") $(shell find $(VENDOR) -name "*.c" -not -path "$(VENDOR)/allegro/*" -not -name "test_*.c")
OBJS      = $(SOURCES:%.c=%.o)

# Some information from Git that we'll use for the version indicator file.
HASH      = $(shell git rev-parse HEAD)
BRANCH    = $(shell git describe --all | sed s@heads/@@ | awk '{print toupper($0)}')
COUNT     = $(shell git rev-list HEAD --count)
DATE      = $(shell date +'%Y-%m-%d %T')

.PHONY: clean dir version
default: all

%.o: %.c
	${CC} -c -o $@ $? ${CFLAGS}

dir:
	@mkdir -p ${DISTDIR}

version:
	@echo "${TITLE}\nBuild: ${COUNT}-${BRANCH} ${DATE}\nHash: ${HASH}" > ${DISTDIR}/version.txt

${DISTDIR}/${BIN}: ${OBJS}
	${CC} -o ${DISTDIR}/${BIN} $+ ${LDFLAGS}

all: dir version ${DISTDIR}/${BIN}

clean:
	rm -rf ${DISTDIR}
	rm -f ${OBJS}
