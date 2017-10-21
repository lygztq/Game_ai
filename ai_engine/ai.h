/*
* @Author: lygztq
* @Date:   2017-10-20 11:30:12
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-20 11:30:12
*/
#include <stdio.h>
#include <cstring>

/** the board size is 15*15, we use a 16*16 size array and do not use 0
	0: empty;	1: BLACK;	2: WHITE
*/

/* some constant */
const int EMPTY = 0;
const int BLACK = 1;
const int WHITE = 2;
const int BOARD_FULL = 3;
const int BOARD_SIZE = 15;

/* some constant for evaluation OR shape names and values*/
const int LIVE[5] = {0,10,100,1000,10000};
const int DEATH[5] = {0,1,10,100,1000};
const int GET_FIVE = 100000;
const int NO_VALUE = 0;

/* Constant for direction */
const int INCREASE = 1;
const int DECREASE = -1;
const int NO_MOVE = 0;

struct bbox
{
	int x_start;
	int y_start;
	int x_end;
	int y_end;
};

/* the board class */
class board
{
private:
	int ** board_look;
	int empty_number;


	bool has_five_line(int color);
public:
	bbox search_grid_domain;

	board();
	~board();
	board(const board &b);
	board(int ** b);
	board & operator=(const board &b);
	int ** get_board(){return board_look;}
	int has_winner(); /*0: no winner;	1: BLACK;	2: WHITE;	3: full board */
	bool add_a_stone(int color, int x, int y);
	bool in_board(int x,int y);
	bool is_empty(int x, int y){return board_look[x][y]==EMPTY;}
	void test_show();
};

/* the ai class */
class ai
{
private:
	int color;
	int search_depth;

	int line_evaluation(int **board_look, int start_x, int start_y, int end_x, int end_y, int x_step, int y_step);
	int max_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth);
	int min_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth);
public:
	ai(int init_color, int init_search_depth=5);
	~ai(){}
	void next_step(board &currnet_board);
	int board_evaluation(int **board_look);
};
