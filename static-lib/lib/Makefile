CC=gcc
LIB=mlc.a
LIBDEST=./


LIBSRC = server.c hashtab.c schedulding.c task_list.c packet.c
LIBOBJ=$(LIBSRC:.c=.o)

CFLAGS = -g -Wall -std=c99
LDFLAGS =


all: $(LIBOBJ)
	@echo lib Makefile - archiving $(LIB)
	@$(AR) r $(LIB) $(LIBOBJ)
.c.o:
	@echo lib Makefile - compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

install:
	cp $(LIB) /usr/lib/mlc/$(LIB)

clean:
	-@rm *.o 2>/dev/null || true
	-@rm $(LIB) 2>/dev/null || true
