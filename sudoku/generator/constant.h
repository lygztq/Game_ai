#ifndef _CONSTANCE_H
#define _CONSTANCE_H

#include <random>
#include <vector>

#define BOARD_SIZE 9
#define ELEMENT_NUM 81
#define MAX_PATH_SIZE 100


extern int random(int x);
extern int random_interval(int l, int h);
extern int * generate_random_seq(int len);
extern void get_index(int ,int &, int &);

#endif