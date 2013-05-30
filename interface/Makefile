CC=gcc
CFLAGS = -g -Wall -std=c99

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = dispatcher
LDLIBS = -levent -lcdk -lncurses

LIBS = ../static-lib/lib

.PHONY: ../static-lib/lib

all: lib $(AOUT)

$(AOUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ ../static-lib/lib/mlc.a $(LDLIBS)

lib:
	$(MAKE) -C ../static-lib/lib

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-@rm *.o 2>/dev/null || true
	-@rm $(AOUT) 2>/dev/null || true
	$(MAKE) -C ../static-lib/lib clean
