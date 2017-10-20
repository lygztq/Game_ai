/*
* @Author: lygztq
* @Date:   2017-10-20 11:30:12
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-20 20:06:14
*/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
// for test begin
#include <random>
#include <windows.h>
// for test end
#include "ai.h"
inline int random(int x){return rand()%x +1;}

/* board class */
board::board()
{
	board_look = new int * [BOARD_SIZE+1];
	for(auto i=1;i<=BOARD_SIZE;++i)
	{
		board_look[i] = new int [BOARD_SIZE+1];
		for(auto j=1;j<=BOARD_SIZE;++j)
			board_look[i][j] = 0;
	}

	empty_number = BOARD_SIZE * BOARD_SIZE;
}

board::~board()
{
	for(auto i=1;i<=BOARD_SIZE;++i)
		delete [] board_look[i];
	delete [] board_look;
}

bool board::add_a_stone(int color, int x, int y)
{
	if(board_look[x][y]!=0)
	{
		printf("already had a stone here.\n");
		return false;
	}
	board_look[x][y] = color;
	return true;
}

int board::has_winner()
{
	if (empty_number==0) return BOARD_FULL;
	else if (has_five_line(BLACK)) return BLACK;
	else if (has_five_line(WHITE)) return WHITE;
	else return EMPTY;
}

inline bool board::in_board(int x, int y)
{
	return (x>0 && x<=BOARD_SIZE && y>0 && y<=BOARD_SIZE);
}

bool board::has_five_line(int color)
{
	/* judge if the player with (int)color already has five stone in a line */
	int length = 0;
	// 8 single directions, 4 bidirections.
	int dx[8] = {-1,1, 0,0, -1,1, -1,1};
	int dy[8] = {0,0, -1,1, -1,1, 1,-1};
	for(auto x=1;x<=BOARD_SIZE;++x)
		for(auto y=1;y<=BOARD_SIZE;++y)
		{
			if(board_look[x][y]!=color) continue;
			for(int i=0;i<8;++i)
			{
				int tx = x + dx[i], ty = y + dy[i];
				if(in_board(tx,ty))
					while(board_look[tx][ty]==color)
					{
						++length;
						tx += dx[i]; ty += dy[i];
						if(!in_board(tx, ty)) break;
					}
				if (i%2)
				{
					++length;
					if(length>=5) return true;
					length = 0; 
				}
			}
		}
	return false;
}

void board::test_show()
{
	printf("test show\n");
	for(auto x=1;x<=BOARD_SIZE;++x)
	{
		for(auto y=1;y<=BOARD_SIZE;++y)
			printf("%d ", board_look[x][y]);
		printf("\n");
	}
}

/* ai class */
inline ai::ai(int init_color, int init_search_depth)
{
	color = init_color;
	search_depth = init_search_depth;
}

void ai::next_step(board &current_board)
{
	/* decide the next step */
	int nx = random(BOARD_SIZE);
	int ny = random(BOARD_SIZE);
	int **board_grid = current_board.get_board();

	while(board_grid[nx][ny]!=EMPTY)
	{
		++nx;
		if(nx>BOARD_SIZE)
		{
			++ny;
			nx = 1;
		}
		if(ny>BOARD_SIZE)
			ny = 1;
	}
	current_board.add_a_stone(color,nx,ny);
	printf("%d %d %d\n",nx,ny,color);
}

// for test main
int main(void)
{
	srand((unsigned)time(NULL));
	int your_x, your_y;
	ai board_ai(BLACK);
	board current_board;
	int state = current_board.has_winner();
	while(state==0 || state==3)
	{
		board_ai.next_step(current_board);
		current_board.test_show();
		scanf("%d %d",&your_x,&your_y);
		current_board.add_a_stone(WHITE,your_x,your_y);
		current_board.test_show();
		state = current_board.has_winner();
	}

	printf("%d\n", state);
	system("PAUSE");
	return EXIT_SUCCESS;
}
