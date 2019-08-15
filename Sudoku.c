#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// sudoku

const int DIM = 9;
const int DIMBOX = 3;
const int EMPTY = 0;


struct sudoku {
	int puzzle[9][9];
	/////////row / col
	int sol[9][9];
};
////////////////////////////////////////////////////////////////////
bool cell_empty(struct sudoku *s, int row, int col) {
	if (s->sol[row][col] == 0) return true;
	return false;
}

bool can_fill_col(struct sudoku *s, int row, int col, int num) {
	for (int i = 0; i < 9; ++i) {
		if (s->sol[i][col] == num) {
			return false;
		}
	}
	return true;
}

bool can_fill_row(struct sudoku *s, int row, int col, int num) {
	for (int i = 0; i < 9; ++i) {
		if (s->sol[row][i] == num) {
			return false;
		}
	}
	return true;
}

bool can_fill_box(struct sudoku *s, int row, int col, int num) {
	int temp_row = 0;
	int temp_col = 0;
	if (row <= 2) {
		temp_row = 0;
	} else if (row <= 5) {
		temp_row = 3;
	} else {
		temp_row = 6;
	}

	if (col <= 2) {
		temp_col = 0;
	} else if (col <= 5) {
		temp_col = 3;
	} else {
		temp_col = 6;
	}


	for (int i = temp_row; i < temp_row + 3; ++i) {
		for (int j = temp_col; j < temp_col + 3; ++j) {
			if (s->sol[i][j] == num) return false;
		}
	}

	return true;
}




/* fill_cell tries to fill num in the cell (row,col).
It returns 0 if doing so does not violate any of the row,
column, and box constraints. Otherwise, it returns a negative
integer.*/

int fill_cell(struct sudoku *s, int row, int col, int num) {
	assert((0 <= row) && (row < 9));
	assert((0 <= col) && (col < 9));
	assert((1 <= num) && (num <= 9));

	if (!cell_empty(s, row, col)) return -5;

	if (can_fill_col(s, row, col, num) && can_fill_row(s, row, col, num)
		&& can_fill_box(s, row, col, num)) {
		s->sol[row][col] = num;
		return 0;
	}

	return -1;
}


//////////////////////////////////////////////////////////////////////


void choices_cell(struct sudoku *s, int row, int col, int choices[], int *num_choices) {
	assert(0 <= col && col <= DIM - 1);
	assert(0 <= row && row <= DIM - 1);
	
	for (int i = 0; i < DIM; ++i) {
		choices[i] = 0;
	}

	*num_choices = 0;

	for (int i = 1; i <= DIM; ++i) {
		if (can_fill_box(s, row, col, i) && can_fill_row(s, row, col, i)
			&& can_fill_col(s, row, col, i) && cell_empty(s, row, col)) {
			choices[*num_choices] = i;
			++(*num_choices);
		}
	}
}

//////////////////////////////////////////////////////////////////
bool check_row(struct sudoku *s) {
	for (int i = 0; i < DIM; ++i) {
		int array[DIM];
		for (int a = 0; a < DIM; ++a) {
			array[a] = 0;
		}

		for (int j = 0; j < DIM; ++j) {
			++(array[s->sol[i][j] - 1]);
		}

		for (int a = 0; a < DIM; ++a) {
			if (array[a] != 1) return false;
		}

	}
	return true;
}

bool check_col(struct sudoku *s) {
	for (int i = 0; i < DIM; ++i) {
		int array[DIM];
		for (int a = 0; a < DIM; ++a) {
			array[a] = 0;
		}

		for (int j = 0; j < DIM; ++j) {
			++(array[s->sol[j][i] - 1]);
		}

		for (int a = 0; a < DIM; ++a) {
			if (array[a] != 1) return false;
		}

	}
	return true;
}

bool check_box(struct sudoku *s) {
	for (int i = 0; i < DIM - 1; i += DIMBOX) {
		for (int j = 0; j < DIM - 1; j += DIMBOX) {

			int array[DIM];
			for (int a = 0; a < DIM; ++a) {
				array[a] = 0;
			}


			for (int x = 0; x < DIMBOX; ++x) {
				for (int y = 0; y < DIMBOX; ++y) {
					++(array[s->sol[i + x][j + y] - 1]);
				}
			}

			for (int a = 0; a < DIM; ++a) {
				if (array[a] != 1) return false;
			}
		}
	}
	return true;
}

bool solved_puzzle(const struct sudoku *s) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			if (cell_empty(s, i, j)) return false;
		}
	}
	if (check_row(s) && check_col(s) && check_box(s)) return true;
	return false;
}



////////////////////////////////////////////////////////////////////

bool solve(struct sudoku *s) {
	if (solved_puzzle(s)) {
		return true;
	}

	int min_choices = DIM;
	int row = 0;
	int col = 0;
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			if (s->sol[i][j] == EMPTY) {
				int c[DIM];
				int n = 0;
				choices_cell(s, i / DIM, i % DIM, c, &n);
				if (n < min_choices) {
					min_choices = n;
					row = i;
					col = j;
				}
				if (n == 1) break;
			}
		}
	}

	int choices[DIM];
	int num_choices = 0;
	choices_cell(s, row, col, choices, &num_choices);

	if (num_choices == 0) {
		return false;
	}

	for (int j = 0; j < num_choices; ++j) {
		s->sol[row][col] = choices[j];
		if (solve(s)) {
			return true;
		}
	}

	s->sol[row][col] = EMPTY;
	return false;
}

////////////////////////////////////////////////////////////////////

/*
int main(void) {

	struct sudoku *s = malloc(sizeof(struct sudoku));

	while (1) {
		printf("Type your sudoku... represent blank spots with 0s:\n");
		char num;

		int list[81];
		int index = 0;
		while (1) {
			scanf(" %c", &num);
			list[index] = num - '0';
			++index;
			if (index == 81) break;
		}
		printf("\n\n");

		for (int i = 0; i < DIM; ++i) {
			for (int j = 0; j < DIM; ++j) {
				s->puzzle[i][j] = s->sol[i][j] = list[DIM * i + j];
				printf("%d", s->puzzle[i][j]);
			}
			printf("\n");
		}

		char c;
		printf("Is this right?\n");
		printf("If not, please press (N/n) or press any key\n");
		scanf(" %c", &c);
		if (!(c == 'n' || c == 'N')) break;
	}
	solve(s);

	printf("ANSWER:\n");

	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			printf("%d", s->sol[i][j]);
		}
		printf("\n");
	}


	free(s);
	return 0;
}*/

char *get_num (char *numbers) {
	struct sudoku *s = malloc(sizeof(struct sudoku));
	//works
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			s->puzzle[i][j] = s->sol[i][j] = numbers[9 * i + j] - '0';
		}
	}
	//works
	solve(s);

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			numbers[9 * i + j] = s->sol[i][j] + '0';
		}
	}
	free(s);
	return numbers;
}


