#!/bin/bash
`g++ -Wall -g -std=c++11 -c minesweeper_board.cpp -o obj/minesweeper_board.o`
`g++ -Wall -g -std=c++11 -c random_part.cpp -o obj/random_part.o`
`g++ -o /bin/minesweeper_board.exe obj/minesweeper_board.o obj/random_part.o`
