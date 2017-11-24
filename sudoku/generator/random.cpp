#include "constant.h"

int random(int x){return rand()%x;}
int random_interval(int l, int h){return random(h-l+1) + l;}

int * generate_random_seq(int len)
{
	int *ret = new int[len];
	std::vector<int> vec;
	for(int i=1;i<=len;++i)
		vec.push_back(i);

	int count = 0;
	while(len>0)
	{
		int index = random(len);
		ret[count++] = vec[index];
		vec.erase(vec.begin() + index);
		--len;
	}

	return ret;
}