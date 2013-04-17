CC=gcc
CFLAGS = -g -Wall
LDFLAGS = -g
LDLIBS = -lfl -lm

AOUT = compiler
OBJS = $(SRC:.c=.o)
SRC = parser.c lexer.c main.c
all: lexparse $(AOUT)

$(AOUT): $(SRC)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

lexparse:
	bison -d parser.y -o parser.c
	flex -o lexer.c lexer.lex

clean:
	@rm parser.c
	@rm parser.h
	@rm lexer.c
	@rm $(AOUT)
