/*
* @Author: lygztq
* @Date:   2017-10-20 11:30:12
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-21 21:03:13
*/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <limits.h>
// for test begin
#include <time.h>
#include <random>
#include <windows.h>
// for test end
#include "ai.h"
inline int random(int x){return rand()%x + 1;}
inline int different_color(int color){return 3 - color;}
inline int abs(int x)
{
	if(x<0) return ~x+1;
	return x; 
}
inline bool is_nab(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2)+abs(y1-y2)<=2;
}

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
	search_grid_domain.x_start = BOARD_SIZE/2;
	search_grid_domain.y_start = BOARD_SIZE/2;
	search_grid_domain.x_end = BOARD_SIZE/2+1;
	search_grid_domain.y_end = BOARD_SIZE/2+1;

	empty_number = BOARD_SIZE * BOARD_SIZE;
}

board::board(int **b)
{
	empty_number = BOARD_SIZE * BOARD_SIZE;
	board_look = new int * [BOARD_SIZE+1];
	search_grid_domain.x_start = BOARD_SIZE/2;
	search_grid_domain.y_start = BOARD_SIZE/2;
	search_grid_domain.x_end = BOARD_SIZE/2+1;
	search_grid_domain.y_end = BOARD_SIZE/2+1;
	
	if(b==NULL)
		for(auto i=1;i<=BOARD_SIZE;++i)
		{
			board_look[i] = new int [BOARD_SIZE+1];
			for(auto j=1;j<=BOARD_SIZE;++j)
				board_look[i][j] = 0;
		}
	else
		for(auto i=1;i<=BOARD_SIZE;++i)
		{
			board_look[i] = new int [BOARD_SIZE+1];
			for(auto j=1;j<=BOARD_SIZE;++j)
			{
				board_look[i][j] = b[i][j];
				if(b[i][j]!=0)
				{
					--empty_number;
					if(i<=search_grid_domain.x_start)
						search_grid_domain.x_start = (i>3)?(i-2):1;
					else if(i>=search_grid_domain.x_end)
						search_grid_domain.x_end = (i+2<BOARD_SIZE)?(i+2):BOARD_SIZE;
					if(j<=search_grid_domain.y_start)
						search_grid_domain.y_start = (j>3)?(j-2):1;
					else if(j>=search_grid_domain.y_end)
						search_grid_domain.y_end = (j+2<BOARD_SIZE)?(j+2):BOARD_SIZE;
				}
			}
		}
}

board::board(const board &b)
{
	board_look = new int *[BOARD_SIZE+1];
	for(auto i=1;i<=BOARD_SIZE;++i)
	{
		board_look[i] = new int [BOARD_SIZE+1];
		for(auto j=1;j<=BOARD_SIZE;++j)
			board_look[i][j] = b.board_look[i][j];
	}
	search_grid_domain = b.search_grid_domain;
	empty_number = b.empty_number;
}

board & board::operator=(const board &b)
{
	if(this == &b) return *this;


	if(board_look==NULL)
	{
		search_grid_domain.x_start = BOARD_SIZE/2;
		search_grid_domain.y_start = BOARD_SIZE/2;
		search_grid_domain.x_end = BOARD_SIZE/2+1;
		search_grid_domain.y_end = BOARD_SIZE/2+1;

		board_look = new int *[BOARD_SIZE+1];
		for(auto i=1;i<=BOARD_SIZE;++i)
		{
			board_look[i] = new int [BOARD_SIZE+1];
			for(auto j=1;j<=BOARD_SIZE;++j)
				board_look[i][j] = b.board_look[i][j];
		}
		empty_number = BOARD_SIZE * BOARD_SIZE;
	}
	else
	{
		for(auto i=1;i<=BOARD_SIZE;++i)
			for(auto j=1;j<=BOARD_SIZE;++j)
				board_look[i][j] = b.board_look[i][j];
		empty_number = b.empty_number;
		search_grid_domain = b.search_grid_domain;
	}
	return *this;
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
	--empty_number; 

	if(x<=search_grid_domain.x_start)
		search_grid_domain.x_start = (x>3)?(x-2):1;
	else if(x>=search_grid_domain.x_end)
		search_grid_domain.x_end = (x+2<BOARD_SIZE)?(x+2):BOARD_SIZE;
	if(y<=search_grid_domain.y_start)
		search_grid_domain.y_start = (y>3)?(y-2):1;
	else if(y>=search_grid_domain.y_end)
		search_grid_domain.y_end = (y+2<BOARD_SIZE)?(y+2):BOARD_SIZE;
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

int ai::line_evaluation(int **board_look, 
						int start_x, 
						int start_y, 
						int end_x, 
						int end_y, 
						int x_step, 
						int y_step)
{
	int ptr_x = start_x, ptr_y = start_y; // current position
	int tmp_x, tmp_y;
	int length;
	int empty_end;
	int evaluate_value_sum = 0;
	while(ptr_x!=end_x || ptr_y!=end_y)
	{
		length = 0;
		empty_end = 0;
		// get the first stone with ai's color
		while(board_look[ptr_x][ptr_y]!=color && (ptr_x!=end_x || ptr_y!=end_y))
		{
			ptr_x += x_step; 
			ptr_y += y_step;
		}
		
		// get the left end of the shape
		if(ptr_x!=start_x || ptr_y!=start_y)
			if(board_look[ptr_x-x_step][ptr_y-y_step]==EMPTY)
				++empty_end;

		// get the length and right end of the shape
		bool over_boundary = false; 
		tmp_x = ptr_x; 
		tmp_y = ptr_y;
		while(board_look[tmp_x][tmp_y]==color)
		{
			++length;
			tmp_x += x_step; tmp_y += y_step;
			if(tmp_x==end_x && tmp_y==end_y)
			{
				if(board_look[tmp_x][tmp_y]==color) ++length;
				else if (board_look[tmp_x][tmp_y]==EMPTY) ++empty_end;
				break;
			}
			over_boundary =  (tmp_x==end_x+x_step && tmp_y==end_y+y_step);
			if(over_boundary) break;
		}
		// check if over boundary.
		if(!over_boundary&&(tmp_x!=end_x || tmp_y!=end_y))
		{
			if (board_look[tmp_x][tmp_y]==EMPTY) ++empty_end;
			ptr_x = tmp_x + x_step; ptr_y = tmp_y + y_step;
		}
		else {ptr_x = tmp_x; ptr_y = tmp_y;}

		if(length>=5) evaluate_value_sum += GET_FIVE;
		if(empty_end==1) evaluate_value_sum += DEATH[length];
		else if(empty_end==2) evaluate_value_sum += LIVE[length];
		if(over_boundary) break;
	}
	return evaluate_value_sum;
}

int ai::board_evaluation(int **board_look)
{
	int evaluation_sum = 0;
	// x-dim
	for(int x=1;x<=BOARD_SIZE;++x)
		evaluation_sum += line_evaluation(board_look, x, 1, x, BOARD_SIZE, NO_MOVE, INCREASE);
	// y-dim
	for(int y=1;y<=BOARD_SIZE;++y)
		evaluation_sum += line_evaluation(board_look, 1, y, BOARD_SIZE, y, INCREASE, NO_MOVE);
	// diagonal
	for(int x=1;x<=BOARD_SIZE;++x)
	{
		evaluation_sum += line_evaluation(board_look, x, 1, 1, x, DECREASE, INCREASE);
		evaluation_sum += line_evaluation(board_look, x, 1, BOARD_SIZE, BOARD_SIZE+1-x, INCREASE, INCREASE);
	}

	for(int y=2;y<=BOARD_SIZE;++y)
	{
		evaluation_sum += line_evaluation(board_look, BOARD_SIZE, y, y, BOARD_SIZE, DECREASE, INCREASE);
		evaluation_sum += line_evaluation(board_look, 1, y, BOARD_SIZE+1-y, BOARD_SIZE, INCREASE, INCREASE);
	}
	return evaluation_sum;
}

int ai::max_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth)
{
	if(depth==search_depth)
		return board_evaluation(b.get_board());

	bbox search_domain = b.search_grid_domain;

	int value = INT_MIN;
	for(int x=search_domain.x_start;x<=search_domain.x_end;++x)
		for(int y=search_domain.y_start;y<=search_domain.y_end;++y)
		{
			if(!b.is_empty(x,y)) continue;
			board next_board(b);
			next_board.add_a_stone(color,x,y);
			int nnx,nny;
			int next_value = min_value(next_board, alpha, beta, nnx, nny, depth+1);
			if(value<next_value)
			{
				value = next_value;
				next_x = x; next_y = y;
			}
			if(beta<=value) return value;
			if(alpha<value) alpha = value;
		}
	return value;
}

int ai::min_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth)
{
	if(depth==search_depth)
		return board_evaluation(b.get_board());

	bbox search_domain = b.search_grid_domain;
	int value = INT_MAX;
	for(int x=search_domain.x_start;x<=search_domain.x_end;++x)
		for(int y=search_domain.y_start;y<=search_domain.y_end;++y)
		{
			if(!b.is_empty(x,y)) continue;
			board next_board(b);
			next_board.add_a_stone(color,x,y);
			int nnx,nny;
			int next_value = max_value(next_board, alpha, beta, nnx, nny, depth+1);
			if(value>next_value)
			{
				value = next_value;
				next_x = x; next_y = y;
			}
			if(alpha>=value) return value;
			if(beta>value) beta = value;
		}
	return value;
}

void ai::next_step(board &current_board)
{
	/* decide the next step */
	int nx, ny;

	// decide next step
	int alpha = INT_MIN, beta = INT_MAX;
	int evaluation_value = max_value(current_board, alpha, beta, nx, ny, 0);
	
	// next step
	current_board.add_a_stone(color,nx,ny);

	// some test
	printf("%d %d %d\n",nx,ny,color);
	printf("board_evaluation: %d\n", board_evaluation(current_board.get_board()));
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
		state = current_board.has_winner();
		if(state==1 || state==2) break;
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
