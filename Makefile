# Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
# MIT License

CC        = $(DJGPP_CC)
VENDOR    = vendor
CFLAGS    =
LDFLAGS   =

BIN       = ceegee.exe
SRCDIR    = src
OBJDIR    = obj
DISTDIR   = dist

SOURCES   = $(shell find $(SRCDIR) -name "*.c") $(shell find $(VENDOR) -name "*.c" -not -path "$(VENDOR)/allegro5/*" -not -name "test_*.c")
OBJS      = $(SOURCES:%.c=%.o)

default: all

%.o: %.c
	${CC} -c -o $@ $? ${CFLAGS}

all: ${OBJS}
	${CC} -o ${DISTDIR}/${BIN} $+ ${LDFLAGS}

clean:
	rm -f ${OBJS}
