CC=gcc
CFLAGS = -Wall -std=c99
LDFLAGS =
LDLIBS = -lcdk -lncurses

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = mylittlecluster

all: $(AOUT)

$(AOUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm *.o
	@rm $(AOUT)

run: all
	@./$(AOUT)

