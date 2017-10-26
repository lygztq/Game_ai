/*
* @Author: lygztq
* @Date:   2017-10-20 11:30:12
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-26 13:14:25
*/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <limits.h>
#include <algorithm>
#include <vector>
// for test begin
#include <time.h>
#include <random>
#include <windows.h>
// for test end
#include "ai.h"

/*some inline function*/
inline int random(int x){return rand()%x + 1;}
inline int different_color(int color){return 3 - color;}
inline int huffman_distance(point p1, point p2) {return abs(p1.x-p2.x)+abs(p1.y-p2.y);}
inline bool is_neighbor(point p1, point p2) {return huffman_distance(p1, p2) <= NEIGHBOR_DISTANCE;}
inline int abs(int x)
{
	if(x<0) return ~x+1;
	return x; 
}

/* cmp for weight point */
bool cmp_weight_point(weight_point p1, weight_point p2){return p1.weight>p2.weight;}

/* board class */

int **board::copy_board(int **b)
{
	int **ans = new int *[BOARD_SIZE+1];
	for(int i=1;i<=BOARD_SIZE;++i)
	{
		ans[i] = new int [BOARD_SIZE+1];
		for(int j=1;j<=BOARD_SIZE;++j)
			ans[i][j] = b[i][j];
	}
	return ans;
}

board::board()
{
	board_look = new int * [BOARD_SIZE+1];
	consider_weight = new int *[BOARD_SIZE+1];
	for(auto i=1;i<=BOARD_SIZE;++i)
	{
		consider_weight[i] = new int [BOARD_SIZE+1];
		board_look[i] = new int [BOARD_SIZE+1];
		for(auto j=1;j<=BOARD_SIZE;++j)
		{
			consider_weight[i][j] = 0;
			board_look[i][j] = 0;
		}
	}
	consider_weight[BOARD_SIZE/2][BOARD_SIZE/2]=1; 
	empty_number = BOARD_SIZE * BOARD_SIZE;
}

/*board::board(int **b)
{
	empty_number = BOARD_SIZE * BOARD_SIZE;
	board_look = new int * [BOARD_SIZE+1];
	if(b==NULL)
	{
		for(auto i=1;i<=BOARD_SIZE;++i)
		{
			board_look[i] = new int [BOARD_SIZE+1];
			for(auto j=1;j<=BOARD_SIZE;++j)
				board_look[i][j] = 0;
		}
		point initial_point(BOARD_SIZE/2,BOARD_SIZE/2);
		candidate_points.push_back(initial_point);
	}
	else
	{
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
}*/

board::board(const board &b)
{
	board_look = new int *[BOARD_SIZE+1];
	consider_weight = new int *[BOARD_SIZE+1];
	for(auto i=1;i<=BOARD_SIZE;++i)
	{
		consider_weight[i] = new int [BOARD_SIZE+1];
		board_look[i] = new int [BOARD_SIZE+1];
		for(auto j=1;j<=BOARD_SIZE;++j)
		{
			consider_weight[i][j] = b.consider_weight[i][j];
			board_look[i][j] = b.board_look[i][j];
		}
	}
	empty_number = b.empty_number;
}

board & board::operator=(const board &b)
{
	if(this == &b) return *this;


	if(board_look==NULL)
	{
		consider_weight = new int *[BOARD_SIZE+1];
		board_look = new int *[BOARD_SIZE+1];
		for(auto i=1;i<=BOARD_SIZE;++i)
		{
			consider_weight[i] = new int [BOARD_SIZE+1];
			board_look[i] = new int [BOARD_SIZE+1];
			for(auto j=1;j<=BOARD_SIZE;++j)
			{
				consider_weight[i][j] = b.consider_weight[i][j];
				board_look[i][j] = b.board_look[i][j];
			}
		}
	}
	else
		for(auto i=1;i<=BOARD_SIZE;++i)
			for(auto j=1;j<=BOARD_SIZE;++j)
			{
				consider_weight[i][j] = b.consider_weight[i][j];
				board_look[i][j] = b.board_look[i][j];
			}
	
	empty_number = b.empty_number;
	return *this;
}

board::~board()
{
	for(auto i=1;i<=BOARD_SIZE;++i)
	{
		delete [] consider_weight[i];
		delete [] board_look[i];
	}
	delete [] consider_weight;
	delete [] board_look;
}

void board::add_neighbor(int x, int y)
{
	int nx,ny;
	int dx[12] = {-2,-1,-1,-1,0,0,0,0,1,1,1,2};
	int dy[12] = {0,-1,0,1,-2,-1,1,2,-1,0,1,0};
	for(int i=0;i<12;++i)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if(!in_board(nx, ny)) continue;
		++consider_weight[nx][ny];
		//if(!is_empty(nx, ny)) continue;
		//if(find(candidate_points.begin(), candidate_points.end(), np)!=candidate_points.end()) continue;
		//candidate_points.push_back(np);
	}
}

void board::remove_neighbor(int x, int y)
{
	int nx,ny;
	int dx[12] = {-2,-1,-1,-1,0,0,0,0,1,1,1,2};
	int dy[12] = {0,-1,0,1,-2,-1,1,2,-1,0,1,0};
	for(int i=0;i<12;++i)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if(!in_board(nx,ny)) continue;
		--consider_weight[nx][ny];
	}
}

bool board::add_a_stone(int color, int x, int y)
{
	if(board_look[x][y]!=0)
	{
		printf("already had a stone here.\n");
		return false;
	}
	board_look[x][y] = color;
	add_neighbor(x,y);
	--empty_number;

	return true;
}

bool board::remove_a_stone(int x, int y)
{
	if(!in_board(x,y)) return false;
	board_look[x][y] = EMPTY;
	remove_neighbor(x,y);
	++empty_number;

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

void board::test_show(int mode)
{
	printf("test show\n");
	if(!mode)
	for(auto x=1;x<=BOARD_SIZE;++x)
	{
		for(auto y=1;y<=BOARD_SIZE;++y)
			printf("%d ", board_look[x][y]);
		printf("\n");
	}
	else
	for(auto x=1;x<=BOARD_SIZE;++x)
	{
		for(auto y=1;y<=BOARD_SIZE;++y)
			printf("%d ", consider_weight[x][y]);
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
						int y_step,
						int judge_color)
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
		// get the first stone with judge color
		while(board_look[ptr_x][ptr_y]!=judge_color && (ptr_x!=end_x || ptr_y!=end_y))
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
		while(board_look[tmp_x][tmp_y]==judge_color)
		{
			++length;
			tmp_x += x_step; tmp_y += y_step;
			if(tmp_x==end_x && tmp_y==end_y)
			{
				if(board_look[tmp_x][tmp_y]==judge_color) ++length;
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

		if(length>=5)  return INT_MAX;//evaluate_value_sum += GET_FIVE;
		if(empty_end==1) evaluate_value_sum += DEATH[length];
		else if(empty_end==2) evaluate_value_sum += LIVE[length];
		if(over_boundary) break;
	}
	return evaluate_value_sum;
}

int ai::board_evaluation(int **board_look)
{
	int evaluation_sum = 0;
	int player_color = different_color(color);
	// x-dim
	for(int x=1;x<=BOARD_SIZE;++x)
	{
		evaluation_sum += line_evaluation(board_look, x, 1, x, BOARD_SIZE, NO_MOVE, INCREASE, color);
		evaluation_sum -= line_evaluation(board_look, x, 1, x, BOARD_SIZE, NO_MOVE, INCREASE, player_color);
	}
	// y-dim
	for(int y=1;y<=BOARD_SIZE;++y)
	{
		evaluation_sum += line_evaluation(board_look, 1, y, BOARD_SIZE, y, INCREASE, NO_MOVE, color);
		evaluation_sum -= line_evaluation(board_look, 1, y, BOARD_SIZE, y, INCREASE, NO_MOVE, player_color);
	}
	// diagonal
	for(int x=1;x<=BOARD_SIZE;++x)
	{
		evaluation_sum += line_evaluation(board_look, x, 1, 1, x, DECREASE, INCREASE, color);
		evaluation_sum += line_evaluation(board_look, x, 1, BOARD_SIZE, BOARD_SIZE+1-x, INCREASE, INCREASE, color);
		evaluation_sum -= line_evaluation(board_look, x, 1, 1, x, DECREASE, INCREASE, player_color);
		evaluation_sum -= line_evaluation(board_look, x, 1, BOARD_SIZE, BOARD_SIZE+1-x, INCREASE, INCREASE, player_color);
	}

	for(int y=2;y<=BOARD_SIZE;++y)
	{
		evaluation_sum += line_evaluation(board_look, BOARD_SIZE, y, y, BOARD_SIZE, DECREASE, INCREASE, color);
		evaluation_sum += line_evaluation(board_look, 1, y, BOARD_SIZE+1-y, BOARD_SIZE, INCREASE, INCREASE, color);
		evaluation_sum -= line_evaluation(board_look, BOARD_SIZE, y, y, BOARD_SIZE, DECREASE, INCREASE, player_color);
		evaluation_sum -= line_evaluation(board_look, 1, y, BOARD_SIZE+1-y, BOARD_SIZE, INCREASE, INCREASE, player_color);
	}
	return evaluation_sum;
}

int ai::max_value(board &b, int &alpha, int &beta, int &next_x, int &next_y, int depth)
{
	if(depth==search_depth)
		return board_evaluation(b.get_board());

	// get the condidates set
	std::vector<weight_point> candidates;
	for(int x=1;x<=BOARD_SIZE;++x)
		for(int y=1;y<=BOARD_SIZE;++y)
		{
			if(b.consider_weight[x][y]!=0 && b.is_empty(x,y))
			{
				weight_point np(x,y,b.consider_weight[x][y]);
				candidates.push_back(np);
			}
		}
	sort(candidates.begin(),candidates.end(),cmp_weight_point);

	int value = INT_MIN;
	int num_of_candidates = candidates.size();
	for(int i=0;i<num_of_candidates;++i)
	{
		int x = candidates[i].x, y = candidates[i].y;
		b.add_a_stone(color,x,y);
		int nnx,nny;
		int next_value = min_value(b, alpha, beta, nnx, nny, depth+1);
		b.remove_a_stone(x,y);
		if(value<next_value)
		{
			value = next_value;
			next_x = x; next_y = y;
		}
		else if(value==next_value)
		{
			int propobility = random(10);
			if(propobility<=2)
			{
				value = next_value;
				next_x = x; next_y = y;
			}
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

	// get candidates
	std::vector<weight_point> candidates;
	for(int x=1;x<=BOARD_SIZE;++x)
		for(int y=1;y<=BOARD_SIZE;++y)
		{
			if(b.consider_weight[x][y]!=0 && b.is_empty(x,y))
			{
				weight_point np(x,y,b.consider_weight[x][y]);
				candidates.push_back(np);
			}
		}
	sort(candidates.begin(),candidates.end(),cmp_weight_point);

	int value = INT_MAX;
	int num_of_candidates = candidates.size();
	for(int i=0;i<num_of_candidates;++i)
	{
		int x = candidates[i].x, y = candidates[i].y;
		b.add_a_stone(different_color(color),x,y);
		int nnx,nny;
		int next_value = max_value(b, alpha, beta, nnx, nny, depth+1);
		b.remove_a_stone(x,y);
		if(value>next_value)
		{
			value = next_value;
			next_x = x; next_y = y;
		}
		else if (value==next_value)
		{
			int propobility = random(10);
			if(propobility<=2)
			{
				value = next_value;
				next_x = x; next_y = y;
			}
		}
		if(alpha >= value) return value;
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
		//current_board.test_show(1);
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


/**
1. change candidate set ok
2. debug
3. alpha-beta cut should sort first ok
4. choose state with same evaluation value randomly ok
5. Why are you(ai) so stupid?
*/
