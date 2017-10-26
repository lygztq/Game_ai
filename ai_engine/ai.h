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
const int NEIGHBOR_DISTANCE = 2;

/* some constant for evaluation OR shape names and values*/
const int LIVE[5] = {0,10,100,1000,10000};
const int DEATH[5] = {0,1,10,100,1000};
const int GET_FIVE = 10000000;
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

struct point
{
	int x;
	int y;
	int id;
	point(){x=0;y=0;id=0;}
	point(int init_x, int init_y):x(init_x),y(init_y){id = (init_x-1)*BOARD_SIZE+init_y;}
	point(int init_id):id(init_id)
	{
		x = init_id/BOARD_SIZE+1;
		y = (init_id-1)%BOARD_SIZE+1;
	}
};

struct weight_point
{
	int x;
	int y;
	int id;
	int weight;
	weight_point(){x=0;y=0;id=0;weight=0;}
	weight_point(int init_x, int init_y, int init_weight):x(init_x),y(init_y),weight(init_weight){id = (init_x-1)*BOARD_SIZE+init_y;}
	weight_point(int init_id, int init_weight):id(init_id),weight(init_weight)
	{
		x = init_id/BOARD_SIZE+1;
		y = (init_id-1)%BOARD_SIZE+1;
	}
};

/* the board class */
class board
{
private:
	int ** board_look;
	  // 0 for not consider
	int empty_number;

	bool has_five_line(int color);
	void add_neighbor(int x, int y);
	void remove_neighbor(int x, int y);
	int **copy_board(int **b);
public:
	int ** consider_weight;
	//vector<point> candidate_points;

	board();
	~board();
	board(const board &b);
	// board(int ** b);
	board & operator=(const board &b);
	int ** get_board(){return board_look;}
	int has_winner(); /*0: no winner;	1: BLACK;	2: WHITE;	3: full board */
	bool add_a_stone(int color, int x, int y);
	bool remove_a_stone(int x, int y);
	bool in_board(int x,int y);
	bool is_empty(int x, int y){return board_look[x][y]==EMPTY;}
	void test_show(int mode=0);
};

/* the ai class */
class ai
{
private:
	int color;
	int search_depth;

	int line_evaluation(int **board_look, int start_x, int start_y, int end_x, int end_y, int x_step, int y_step, int judge_color);
	int max_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth);
	int min_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth);
public:
	ai(int init_color, int init_search_depth=5);
	~ai(){}
	void next_step(board &currnet_board);
	int board_evaluation(int **board_look);
};
