#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "random_part.h"

// default board size
const int PRIMARY_SIZE[3] = {9, 9, 10};
const int MIDDLE_SIZE[3] = {16, 16, 40};
const int SENIOR_SIZE[3] = {16, 30, 99};

// state of exploration domain
const int UNEXPLORATED = 0;
const int EXPLORATED = 1;
const int MARKED = 2;
const int UNCERTAIN = 3;

// state of mine distribution
const int MINE = -1;
const int NONE = 0;
const int HAS_MINE_NEARLY[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};


struct point
{
	int first_index;
	int second_index;
	point(){first_index = 0; second_index = 0;}
	point(int f, int s):first_index(f),second_index(s){}
};


class minesweeper_board
{
private:
	int first_dim_length;
	int second_dim_length;
	int mine_num;
	int ** mine_distribution; //-1 for mine, 0 for none, i>0 for num of adjcent mine
	int ** exploration_domain;

	void expand(int first_index, int second_index);
	void initialization(int first_length, int second_length, int num_of_mine);
	void id_to_point(int id, int &first_index, int &second_index)
	{
		first_index = id / second_dim_length;
		second_index = id % second_dim_length;
	}
public:
	// initialization function
	minesweeper_board(int first_length, int second_length, int num_of_mine)
	{
		// error case
		if(num_of_mine>first_length*second_length) ;
		initialization(first_length,second_length,num_of_mine);
	}
	minesweeper_board(char degree)
	{
		/* degree: P,M,S*/
		switch(degree)
		{
			case 'P':
				initialization(PRIMARY_SIZE[0], PRIMARY_SIZE[1], PRIMARY_SIZE[2]);
				break;
			case 'M':
				initialization(MIDDLE_SIZE[0], MIDDLE_SIZE[1], MIDDLE_SIZE[2]);
				break;
			case 'S':
				initialization(SENIOR_SIZE[0], SENIOR_SIZE[1], SENIOR_SIZE[2]);
				break;
			default:
				// error case
				perror("Wrong input char");
		}
	}
	// basic operation
	bool explore(int first_index, int second_index); // return false if get a mine
	void mark(int first_index, int second_index);
	void not_sure(int first_index, int second_index);
	// state check
	bool has_mine(int first_index, int second_index){return mine_distribution[first_index][second_index]==-1;}
	// get board
	int ** get_mine_distribution(){return mine_distribution;}
	int ** get_exploration_domain(){return exploration_domain;}
	// boundary check
	bool in_board(int first_index, int second_index){return first_index>=0 && first_index<first_dim_length && second_index>=0 && second_index<second_dim_length;}
	// debug
	void test_show(int mode);
};
