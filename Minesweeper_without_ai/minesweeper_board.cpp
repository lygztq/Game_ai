/*
* @Author: lygztq
* @Date:   2017-10-31 10:07:03
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-31 18:00:49
*/
#include "random_part.h"
#include "minesweeper_board.h"

void minesweeper_board::expand(int first_index, int second_index)
{
	int df[8] = {-1,0,1,-1,1,-1,0,1};
	int ds[8] = {-1,-1,-1,0,0,1,1,1};
	exploration_domain[first_index][second_index] = EXPLORATED;
	if(mine_distribution[first_index][second_index] > 0) return;

	for(int i=0;i<8;++i)
	{
		int nf = first_index+df[i], ns = second_index+ds[i];
		if(!in_board(nf,ns)) continue;
		if(exploration_domain[nf][ns]==EXPLORATED) continue;
		expand(nf,ns);
	}
}

void minesweeper_board::initialization(int first_length, int second_length, int num_of_mine)
{
	/**
		generalization of mine_distribution and exploration_domain
	*/
	int df[8] = {-1,0,1,-1,1,-1,0,1};
	int ds[8] = {-1,-1,-1,0,0,1,1,1};
	first_dim_length = first_length;
	second_dim_length = second_length;
	mine_num = num_of_mine;
	mine_distribution = new int *[first_dim_length];
	exploration_domain = new int *[first_dim_length];
	for(int i=0;i<first_dim_length;++i)
	{
		mine_distribution[i] = new int [second_dim_length];
		exploration_domain[i] = new int [second_dim_length];
		for(int j=0;j<second_dim_length;++j)
		{
			mine_distribution[i][j] = NONE;
			exploration_domain[i][j] = UNEXPLORATED;
		}
	}

	std::vector<int> id_queue;
	int total_id_num = first_dim_length*second_dim_length;
	for(int i=0;i<total_id_num;++i)
		id_queue.push_back(i);

	for(int i=0;i<mine_num;++i)
	{
		int id_index = random_index((int)(id_queue.size()));
		int mine_first_index, mine_second_index;
		id_to_point(id_queue[id_index],mine_first_index,mine_second_index);
		//printf("mine index: %d %d\n",mine_first_index,mine_second_index);
		id_queue.erase(id_queue.begin() + id_index);
		mine_distribution[mine_first_index][mine_second_index] = MINE;
		for(int j=0;j<8;++j)
		{
			if(!in_board(mine_first_index+df[j], mine_second_index+ds[j]))
				continue;
            if(mine_distribution[mine_first_index+df[j]][mine_second_index+ds[j]]!=-1)
                mine_distribution[mine_first_index+df[j]][mine_second_index+ds[j]]+=1;
		}
	}
}

bool minesweeper_board::explore(int first_index, int second_index)
{
	// error case
	if(!in_board(first_index,second_index)) ;
	if(exploration_domain[first_index][second_index]!=UNEXPLORATED) return true;

	// get mine
	if(mine_distribution[first_index][second_index]==MINE) return false;
	// else get number
	else if(mine_distribution[first_index][second_index]!=0)
	{
		exploration_domain[first_index][second_index] = EXPLORATED;
		return true;
	}
	// else get none
	else
		expand(first_index, second_index);

	//if(mine_distribution[first_index][second_index]==)
	return true;
}

void minesweeper_board::mark(int first_index, int second_index)
{
	// error case
	if(!in_board(first_index,second_index)) ;

	if(exploration_domain[first_index][second_index]==UNEXPLORATED)
	{
		exploration_domain[first_index][second_index] = MARKED;
		return;
	}
}

void minesweeper_board::not_sure(int first_index, int second_index)
{
	// error case
	if(!in_board(first_index,second_index)) ;

	if(exploration_domain[first_index][second_index]==MARKED)
	{
		exploration_domain[first_index][second_index] = UNCERTAIN;
		return;
	}
}

void minesweeper_board::test_show(int mode)
{
	if(mode == 0)
	{
		for(int i=0;i<first_dim_length;++i)
		{
			for(int j=0;j<second_dim_length;++j)
			{
				if(exploration_domain[i][j]==EXPLORATED)
					printf("%d\t", mine_distribution[i][j]);
				else if(exploration_domain[i][j]==UNEXPLORATED)
					printf("*\t");
			}
			printf("\n\n");
		}
	}
	else
	{
		for(int i=0;i<first_dim_length;++i)
		{
			for(int j=0;j<second_dim_length;++j)
				printf("%d  ", exploration_domain[i][j]);
			printf("\n\n");
		}
	}
}

// test main
 int main(void)
 {
 	srand((int)time(0));
 	minesweeper_board board(20,20,50);
 	board.test_show(0);

 	for(int i=0;i<100;++i)
 	{
 		int nx,ny;
 		scanf("%d %d",&nx,&ny);
 		board.explore(nx,ny);
 		board.test_show(0);
 	}

 	system("PAUSE");
 	return 0;
 }
