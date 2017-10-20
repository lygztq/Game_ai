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

/* the board class */
class board
{
private:
	int ** board_look;
	int empty_number;

	bool has_five_line(int color);
public:
	board();
	~board();
	int ** get_board(){return board_look;}
	int has_winner(); /*0: no winner;	1: BLACK;	2: WHITE;	3: full board */
	bool add_a_stone(int color, int x, int y);
	void test_show();
};

/* the ai class */
class ai
{
private:
	int color;
public:
	board current_board;
	ai(int init_color);
	~ai(){}
	void next_step();

};