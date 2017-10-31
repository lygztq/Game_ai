/*
* @Author: lygztq
* @Date:   2017-10-31 09:57:51
* @Last Modified by:   lygztq
* @Last Modified time: 2017-10-31 11:33:25
*/
#include "random_part.h"

int random_index(int length) {return rand()%length;}
int random_int(int lower, int upper) {return random_index(upper-lower+1) + lower;}
double unit_random_num() {return rand() / double(RAND_MAX);}
