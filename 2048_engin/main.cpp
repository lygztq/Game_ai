#include<stdio.h>
#include<random>
#include<time.h>
#include<windows.h>
#include<cstring>
#include<vector>
#include<algorithm>
#define BORDER_LENGTH 4
using namespace std;

inline int random(int x){return rand()%x;}


class idSet
{
public:
    idSet(){current_number=0;}
    int getCurrentNum(){return current_number;}
    void pushBack(int id){ids[current_number++]=id;}
    int findId(int id)
    {
        for(int i=0;i<current_number;++i)
            if(ids[i]==id) return i;
        return -1;
    }
    void removeId(int index)
    {
        if(index!=current_number-1)
            for(int i=index;i<current_number-1;++i)
                ids[i] = ids[i+1];
        --current_number;
    }
    int getRandomId()
    {
        srand((unsigned)time(NULL));
        int index = random(current_number);
        int ans = ids[index];
        removeId(index);
        return ans;
    }
    int & operator[](int index){return ids[index];}
private:
    int ids[16];
    int current_number;
};


/*
x for row and y for col
*/
class board
{
public:
    board()
    {
        //initial play board
        memset(play_board,0,sizeof(play_board));

        //get first block
        int initial_value = (getRandomNum(0,1))?4:2;  //0:2, 1:4
        int initial_x = getRandomNum(0,BORDER_LENGTH-1);
        Sleep(500);
        int initial_y = getRandomNum(0,BORDER_LENGTH-1);
        for(int i=0;i<BORDER_LENGTH*BORDER_LENGTH;++i)
            id_set.pushBack(i);
        int initial_id = getId(initial_x,initial_y);
        id_set.removeId(id_set.findId(initial_id));

        //initial data
        play_board[initial_x][initial_y] = initial_value;
        total_block_number = 1;
        max_block_value = initial_value;

        show();
        printf("Use w,s,a,d for up, down, left, right.\n");
    }

    void show()
    {
        for(int x=0;x<BORDER_LENGTH;++x)
        {
            for(int y=0;y<BORDER_LENGTH;++y)
            {
                printf("%d\t",play_board[x][y]);
            }
            printf("\n");
        }
        printf("\n\n");
    }

    void nextValue()
    {
        int next_value = (getRandomNum(0,1))?4:2;
        int next_x, next_y;
        if(id_set.getCurrentNum()==0) return;
        int next_id = id_set.getRandomId();
        getIndex(next_id,next_x,next_y);

//        while(play_board[next_x][next_y]!=0)
//        {
//        	next_index = getRandomNum(0,blank_num-1);
//        	next_id = id_set[next_index];
//        	getIndex(next_id,next_x,next_y);
//		}
        play_board[next_x][next_y] = next_value;
        ++total_block_number;
        max_block_value = (next_value>max_block_value)?next_value:max_block_value;
    }

    void goUp()
    {
        bool has_union[4];
        memset(has_union,0,sizeof(has_union));

        for(int x=1;x<BORDER_LENGTH;++x)
        {
            for(int y=0;y<BORDER_LENGTH;++y)
            {
                if(!play_board[x][y]) continue;
                bool exchanged = false;
                for(int up_x=x-1;up_x>=0;--up_x)
                {
                    if(!play_board[up_x][y]) continue;
                    else if(has_union[y] || play_board[x][y]!=play_board[up_x][y])
                    {
                    	if(up_x+1!=x)
                    	{
                    		play_board[up_x+1][y] = play_board[x][y];
                        	play_board[x][y] = 0;
                        	id_set[id_set.findId(getId(up_x+1,y))] = getId(x,y);
						}
                        exchanged = true;
                        //show();
                        break;
                    }
                    else
                    {
                        play_board[x][y] = 0;
                        play_board[up_x][y]*=2;
                        id_set.pushBack(getId(x,y));
                        max_block_value = (play_board[up_x][y]>max_block_value)?play_board[up_x][y]:max_block_value;
                        --total_block_number;
                        exchanged = true;
                        has_union[y] = true;
                        //show();
                        break;
                    }
                }
                if(!exchanged)
                {
                    play_board[0][y] = play_board[x][y];
                    play_board[x][y] = 0;
                    id_set[id_set.findId(getId(0,y))] = getId(x,y);
                }
            }
        }
        nextValue();
    }

    void goDown()
    {
        bool has_union[4];
        memset(has_union,0,sizeof(has_union));

        for(int x=BORDER_LENGTH-2;x>=0;--x)
        {
            for(int y=0;y<BORDER_LENGTH;++y)
            {
                if(!play_board[x][y]) continue;
                bool exchanged = false;
                for(int down_x=x+1;down_x<BORDER_LENGTH;++down_x)
                {
                    if(!play_board[down_x][y]) continue;
                    else if(has_union[y] || play_board[down_x][y]!=play_board[x][y])
                    {
                    	if(down_x-1!=x)
                    	{
                    		play_board[down_x-1][y] = play_board[x][y];
                        	play_board[x][y] = 0;
                        	id_set[id_set.findId(getId(down_x-1,y))] = getId(x,y);
						}
                        exchanged = true;
                        break;
                    }
                    else
                    {
                        play_board[x][y] = 0;
                        play_board[down_x][y] *= 2;
                        id_set.pushBack(getId(x,y));
                        max_block_value = (play_board[down_x][y]>max_block_value)?play_board[down_x][y]:max_block_value;
                        --total_block_number;
                        exchanged = true;
                        has_union[y] = true;
                        break;
                    }
                }
                if(!exchanged)
                {
                    play_board[BORDER_LENGTH-1][y] = play_board[x][y];
                    play_board[x][y] = 0;
                    id_set[id_set.findId(getId(BORDER_LENGTH-1,y))] = getId(x,y);
                }
            }
        }
        nextValue();
    }

    void goLeft()
    {
        bool has_union[4];
        memset(has_union,0,sizeof(has_union));

        for(int y=1;y<BORDER_LENGTH;++y)
        {
            for(int x=0;x<BORDER_LENGTH;++x)
            {
                if(!play_board[x][y]) continue;
                bool exchanged = false;
                for(int left_y=y-1;left_y>=0;--left_y)
                {
                    if(!play_board[x][left_y]) continue;
                    else if(has_union[x] || play_board[x][y]!=play_board[x][left_y])
                    {
                    	if(left_y+1!=y)
						{
							play_board[x][left_y+1] = play_board[x][y];
                        	play_board[x][y] = 0;
                        	id_set[id_set.findId(getId(x,left_y+1))] = getId(x,y);
						}
                        exchanged = true;
                        break;
                    }
                    else
                    {
                        play_board[x][left_y]*=2;
                        play_board[x][y] = 0;
                        id_set.pushBack(getId(x,y));
                        max_block_value = (play_board[x][left_y]>max_block_value)?play_board[x][left_y]:max_block_value;
                        --total_block_number;
                        has_union[x] = true;
                        exchanged = true;
                        break;
                    }
                }
                if(!exchanged)
                {
                    play_board[x][0] = play_board[x][y];
                    play_board[x][y] = 0;
                    id_set[id_set.findId(getId(x,0))] = getId(x,y);
                }
            }
        }
        nextValue();
    }

    void goRight()
    {
        bool has_union[4];
        memset(has_union,0,sizeof(has_union));

        for(int y=BORDER_LENGTH-2;y>=0;--y)
        {
            for(int x=0;x<BORDER_LENGTH;++x)
            {
                if(!play_board[x][y]) continue;
                bool exchanged = false;
                for(int right_y=y+1;right_y<BORDER_LENGTH;++right_y)
                {
                    if(!play_board[x][right_y]) continue;
                    else if(has_union[x] || play_board[x][y]!=play_board[x][right_y])
                    {
                    	if(right_y-1!=y)
                    	{
                    		play_board[x][right_y-1] = play_board[x][y];
                        	play_board[x][y] = 0;
                        	id_set[id_set.findId(getId(x,right_y-1))] = getId(x,y);
						}
                        exchanged = true;
                        break;
                    }
                    else
                    {
                        play_board[x][y] = 0;
                        play_board[x][right_y]*=2;
                        id_set.pushBack(getId(x,y));
                        max_block_value = (play_board[x][right_y]>max_block_value)?play_board[x][right_y]:max_block_value;
                        --total_block_number;
                        exchanged = true;
                        has_union[x] = true;
                        break;
                    }
                }
                if(!exchanged)
                {
                    play_board[x][BORDER_LENGTH-1] = play_board[x][y];
                    play_board[x][y] = 0;
                    id_set[id_set.findId(getId(x,BORDER_LENGTH-1))] = getId(x,y);
                }
            }
        }
        nextValue();
    }

    bool notStationary()
    {
        bool ans = false;
        int dx[4]={1,-1,0,0};
        int dy[4]={0,0,1,-1};
        for(int x=0;x<BORDER_LENGTH;++x)
        {
            for(int y=0;y<BORDER_LENGTH;++y)
            {
                int tmp_ans=0;
                for(int i=0;i<4;++i)
                    tmp_ans+=hasOperation(play_board[x][y],x,y,dx[i],dy[i]);
                if(tmp_ans!=0)
                    return true;
            }
        }
        return ans;
    }

    int getMaxValue(){return max_block_value;}
    int getTotalNum(){return total_block_number;}
private:
    int play_board[BORDER_LENGTH][BORDER_LENGTH];
    int total_block_number;
    int max_block_value;
    idSet id_set;

    bool hasOperation(int curr_value,int x,int y,int dx,int dy)
    {
        bool ans = false;
        int tx = x+dx,ty = y+dy;
        while((tx>=0 && tx<BORDER_LENGTH) && (ty>=0 && ty<BORDER_LENGTH))
        {
            if(!play_board[tx][ty])
            {
                tx += dx; ty += dy;
                continue;
            }
            else if(play_board[tx][ty]!=curr_value) break;
            else {ans = true;break;}
        }
        return ans;
    }
    void getIndex(int id, int &x, int &y)
    {
        x = id/BORDER_LENGTH;
        y = id%BORDER_LENGTH;
    }
    int getId(int x, int y) {return x*BORDER_LENGTH+y;}
    int getRandomNum(int lower, int upper)
    {
        /*get integer in [lower, upper]*/
        Sleep(100);
        srand((unsigned)time(NULL));
        int length = upper-lower+1;
        return random(length)+lower;
    }
};

int main()
{
    board UI;
    char op;

    while(true)
    {
        printf("next operation:\n");
        scanf("%s",&op);
        switch(op)
        {
            case 'w':UI.goUp();break;
            case 's':UI.goDown();break;
            case 'a':UI.goLeft();break;
            case 'd':UI.goRight();break;
        }
        printf("\ncurrent board.\n");
    	UI.show();
        if(UI.getMaxValue()==2048)
        {
            printf("you win.\n");
            break;
        }
        if(UI.getTotalNum()>=16)
        {
            if(!UI.notStationary())
            {
                printf("you lose.\n");
                break;
            }
        }
    }

    return 0;
}
