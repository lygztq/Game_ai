#ifndef _INSTANCE_READER_h
#define _INSTANCE_READER_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"

class instance_reader
{
private:
	char file_path[MAX_PATH_SIZE];
	int instance[BOARD_SIZE][BOARD_SIZE];
public:
	instance_reader(int seed);
	int read_item(int r,int c){return instance[r][c];}
	int * read_line(int r){return &instance[r][0];}
	void test_show()
	{
		for(int i=0;i<BOARD_SIZE;++i)
		{
			for(int j=0;j<BOARD_SIZE;++j)
				printf("%d ", instance[i][j]);
			printf("\n");
		}
	}
};

#endif