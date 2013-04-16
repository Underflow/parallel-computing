CC=gcc
CFLAGS = -g -Wall -std=c99

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = pi_client 

all: $(AOUT)

$(AOUT): $(OBJS)
	$(CC) -m32 $(LDFLAGS) -o $@ $^ $(LDLIBS)
%.o : %.c
	$(CC) -m32 $(CFLAGS) -o $@ -c $<

clean:
	@rm *.o
	@rm $(AOUT)
