#include "stdio.h"
#include "stdlib.h"

void print_table(char* t) {
	printf("   | a | b | c\n");
	printf("---+---+---+---\n");
	printf(" 1 | %c | %c | %c\n", t[0], t[1], t[2]);
	printf("---+---+---+---\n");
	printf(" 2 | %c | %c | %c\n", t[3], t[4], t[5]);
	printf("---+---+---+---\n");
	printf(" 3 | %c | %c | %c\n", t[6], t[7], t[8]);
}

char check_win(char* t) {
	if (t[0] != ' ' && t[0] == t[1] && t[1] == t[2]) return t[0];
	if (t[3] != ' ' && t[3] == t[4] && t[4] == t[5]) return t[3];
	if (t[6] != ' ' && t[6] == t[7] && t[7] == t[8]) return t[6];

	if (t[0] != ' ' && t[0] == t[3] && t[3] == t[6]) return t[0];
	if (t[1] != ' ' && t[1] == t[4] && t[4] == t[7]) return t[1];
	if (t[2] != ' ' && t[2] == t[5] && t[5] == t[8]) return t[2];

	if (t[0] != ' ' && t[0] == t[4] && t[4] == t[8]) return t[0];
	if (t[2] != ' ' && t[2] == t[4] && t[4] == t[6]) return t[2];

	for (int i = 0; i < 9; i++) if (t[i] == ' ') return ' ';
	return 'D';
}

int* available_moves(char* table) {
	int* moves = malloc(9 * sizeof(int));
	int m = 0;
	for (int i = 0; i < 9; i++)
		if (table[i] == ' ')
			moves[m++] = i;
	if (m < 9)
		moves[m] = -1;
	return moves;
}

int get_line_score(char* table, char player, int a, int b, int c) {
	int score = 0;
	
	if (table[a] == player) score = 1;
	else if (table[a] != ' ') score = -1;
	
	if (table[b] == player) {
		if (score == 1) score = 10;
		else if (score == -1) return 0;
		else score = 1;
	} else if (table[b] != ' ') {
		if (score == -1) score = -10;
		else if (score == 1) return 0;
		else score = -1;
	}

	if (table[c] == player) {
		if (score > 0) score *= 10;
		else if (score < 0) return 0;
		else score = 1;
	} else if (table[c] != ' ') {
		if (score < 0) score *= 10;
		else if (score > 0) return 0;
		else score = -1;
	}

	return score;
}

int get_score(char* table, char player) {
	int score = 0;

	score += get_line_score(table, player, 0, 1, 2);
	score += get_line_score(table, player, 3, 4, 5);
	score += get_line_score(table, player, 6, 7, 8);

	score += get_line_score(table, player, 0, 3, 6);
	score += get_line_score(table, player, 1, 4, 7);
	score += get_line_score(table, player, 2, 5, 8);

	score += get_line_score(table, player, 0, 4, 8);
	score += get_line_score(table, player, 2, 4, 6);

	return score;
}

int negamax(char* table, int depth, char player) {
	if (check_win(table) != ' ')
		return get_score(table, player);
	int best_score = -10000;
	int best_move;
	int* moves = available_moves(table);
	for (int i = 0; i < 9; i++) {
		if (moves[i] == -1)
			break;
		table[moves[i]] = player;
		int score = -negamax(table, depth + 1, player == 'X' ? 'O' : 'X');
		if (score > best_score) {
			best_score = score;
			best_move = moves[i];
		}
		table[moves[i]] = ' ';
	}
	if (depth == 0)
		table[best_move] = player;
	return best_score;
}

int get_input() {
	char *line = NULL;
	size_t line_length = 0;

	char x = -1, y = -1;
	while (x < 0 || x > 2 || y < 0 || y > 2) {
		printf("> ");
		int read = getline(&line, &line_length, stdin);
		if (read < 2)
			continue;
		x = line[0] - 'a';
		y = line[1] - '1';
	}
	return x + 3 * y;
}

int main(int argc, char** argv) {
	char table[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	char turn = 'X';
	char computer = argc > 1 ? argv[1][0] : 'O';
	if (computer != 'X' && computer != 'O') {
		printf("Invalid argument.\n");
		exit(1);
	}
	while (1) {
		char win = check_win(table);
		if (win == 'D') {
			print_table(table);
			printf("It's a draw!\n");
			break;
		} else if (win != ' ') {
			print_table(table);
			printf("%c won!\n", win);
			break;
		}

		if (turn == computer) {
			negamax(table, 0, computer);
		} else {
			print_table(table);
			int move;
			do move = get_input();
			while (table[move] != ' ');
			table[move] = turn;
		}
		turn = turn == 'X' ? 'O' : 'X';
	};
}
