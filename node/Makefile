CC=gcc
CFLAGS = -g -Wall -std=c99

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = node

all: $(AOUT)

$(AOUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm *.o
	@rm $(AOUT)
