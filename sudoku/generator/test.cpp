#include "sudoku_generator.h"
#include "sudoku_server.h"
#include "constant.h"
#include <windows.h>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	srand((unsigned)time(NULL));
	sudoku_generator generator(40);

	generator.test_show();

	sudoku_server server;
	if(server.judge_correct(generator.get_board()))
	{
		printf("currect!\n");
	}

	system("PAUSE");

	return 0;
}