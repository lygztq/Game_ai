/*
* @Author: lygztq
* @Date:   2017-10-20 11:30:12
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-20 12:04:03
*/
#include <stdio.h>
#include <cstring>
#include "ai.h"

/** the board size is 15*15, we use a 16*16 size array and do not use 0
	0: empty;	1: BLACK;	2: WHITE
*/


//#############################################################################
/* some constant */
// const int EMPTY = 0;
// const int BLACK = 1;
// const int WHITE = 2；
// const int BOARD_FULL = 3;
// const int BOARD_SIZE = 15;

// /* the board class */
// class board
// {
// private:
// 	int ** board_look;
// 	int empty_number;

// 	bool has_five_line(int color);
// public:
// 	board();
// 	~board();
// 	int ** get_board(){return board_look;}
// 	int has_winner(); /*0: no winner;	1: BLACK;	2: WHITE;	3: full board */
// 	bool add_a_stone(int color, int x, int y);
// };

// /* the ai class */
// class ai
// {
// private:
// 	int color;
// public:
// 	board current_board;
// 	ai(int color);
// 	~ai();
// 	void next_step();
// };
//#############################################################################


/* board class */
board::board()
{
	board_look = new int * [BOARD_SIZE+1];
	for(auto i=1;i<=BOARD_SIZE;++i)
		board_look[i] = new int [BOARD_SIZE+1];
	memset(board_look,0,sizeof(board_look));

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

bool board::has_five_line(int color)
{
	/* judge if the player with (int)color already has five stone in a line */
}
/* ai class */
ai::ai(int init_color)
{
	color = init_color;
}

void ai::next_step()
{
	/* decide the next step */
}