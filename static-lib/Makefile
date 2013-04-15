CC=gcc
CFLAGS = -g -Wall -std=c99

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = dispatcher
LDLIBS = -levent

LIBS = lib

.PHONY: lib

all: lib $(AOUT)

$(AOUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ lib/mlc.a $(LDLIBS)

lib:
	$(MAKE) -C lib

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-@rm *.o 2>/dev/null || true
	-@rm $(AOUT) 2>/dev/null || true
	$(MAKE) -C lib clean
