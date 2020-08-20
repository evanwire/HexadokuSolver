all: hex

hex:
	gcc -g -Wall -Werror -fsanitize=address -std=c11 hex.c -o hex

clean:
	rm -rf hex
