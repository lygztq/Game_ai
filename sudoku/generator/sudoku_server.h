#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "constant.h"

class sudoku_server
{
public:
	bool judge_correct(int **curr_board);
};

#endif