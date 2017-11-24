#ifndef _GENERATOR_H
#define _GENERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include "instance_reader.h"
#include "constant.h"

class sudoku_generator
{
private:
	int *replace_line;
	int reverse_find_table[BOARD_SIZE+1];
	int num_deleted;
public:
	sudoku_generator(int num_d);
	~sudoku_generator(){delete [] replace_line;}
	bool ** get_mask();
	int ** get_board();
	void test_show();
};

#endif
