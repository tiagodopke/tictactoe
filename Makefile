tictactoe: tictactoe.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f tictactoe

run: tictactoe
	./$<
