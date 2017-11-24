#include "sudoku_server.h"

bool sudoku_server::judge_correct(int **curr_board)
{
	bool judge_set[BOARD_SIZE+1];
	memset(judge_set,0,sizeof(judge_set));

	bool judge_signal = true;

	// lines
	for(int i=0;i<BOARD_SIZE;++i)
	{
		for(int j=0;j<BOARD_SIZE;++j)
		{
			if(judge_set[curr_board[i][j]]==judge_signal) return false;
			judge_set[curr_board[i][j]] = judge_signal;
		}
		judge_signal = !judge_signal;
	}

	// cols
	for(int j=0;j<BOARD_SIZE;++j)
	{
		for(int i=0;i<BOARD_SIZE;++i)
		{
			if(judge_set[curr_board[i][j]]==judge_signal) return false;
			judge_set[curr_board[i][j]] = judge_signal;
		}
		judge_signal = !judge_signal;
	}

	// 3*3 blocks
	int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dy[9] = {1, 0 ,-1, 1, 0, -1, 1, 0, -1};
	int point_index[3] = {1,4,7};
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			int center_x = point_index[i],
				center_y = point_index[j];

			for(int k=0;k<9;++k)
			{
				int curr_x = center_x + dx[k],
					curr_y = center_y + dy[k];

				if(judge_set[curr_board[curr_x][curr_y]]==judge_signal) return false;
				judge_set[curr_board[curr_x][curr_y]] = judge_signal;
			}
			judge_signal = !judge_signal;
		}
	}

	return true;
}