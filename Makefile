CC = gcc
CFLAGS = -std=c99
doenv: doenv.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f doenv
