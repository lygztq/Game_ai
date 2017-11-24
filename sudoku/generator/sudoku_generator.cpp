#include "sudoku_generator.h"

void get_index(int id, int &r, int &c)
{
	r = id/BOARD_SIZE;
	c = id%BOARD_SIZE;
}

sudoku_generator::sudoku_generator(int num_d)
{
	num_deleted = num_d;
	replace_line = generate_random_seq(BOARD_SIZE);
	for(int i=0;i<BOARD_SIZE;++i)
	{
		reverse_find_table[replace_line[i]] = i;
	}
}

bool ** sudoku_generator::get_mask()
{
	bool ** mask = new bool * [BOARD_SIZE];
	for(int l=0;l<BOARD_SIZE;++l)
	{
		mask[l] = new bool [BOARD_SIZE];
		for(int c=0;c<BOARD_SIZE;++c)
			mask[l][c] = true;
	}

	int *deleted_line = generate_random_seq(ELEMENT_NUM);

	for(int i=0;i<num_deleted;++i)
	{
		int row,col;
		get_index(deleted_line[i]-1,row,col);
		//printf("%d %d %d \n", row, col, num_deleted);
		mask[row][col] = false;
	}

	delete [] deleted_line;
	return mask;
}

int ** sudoku_generator::get_board()
{
	instance_reader reader(random(20));
	int ** board = new int * [BOARD_SIZE];
	for(int l=0;l<BOARD_SIZE;++l)
	{
		board[l] = new int [BOARD_SIZE];
		for(int c=0;c<BOARD_SIZE;++c)
		{
			int elem = reader.read_item(l,c);
			int replace_index = (reverse_find_table[elem] + 1) % BOARD_SIZE;
			board[l][c] = replace_line[replace_index];
		}
	}

	return board;
}

void sudoku_generator::test_show()
{
	printf("The board:\n---------\n");
	int ** board = get_board();
	for(int i=0;i<BOARD_SIZE;++i)
	{
		for(int j=0;j<BOARD_SIZE;++j)
			printf("%d ", board[i][j]);
		printf("\n");
	}
	printf("\n\nthe mask:\n---------\n");

	bool ** mask = get_mask();
	for(int i=0;i<BOARD_SIZE;++i)
	{
		for(int j=0;j<BOARD_SIZE;++j)
			printf("%d ", mask[i][j]);
		printf("\n");
	}
}

