CC = gcc
CFLAGS = -Wall -Wextra -g

compiler: main.c lexer.c
	$(CC) $(CFLAGS) -o compiler main.c lexer.c

clean:
	rm -f compiler