@echo off
g++ -c minesweeper_board.cpp -o obj/minesweeper_board.o
g++ -c random_part.cpp -o obj/random_part.o
g++ obj/random_part.o obj/minesweeper_board.o -o bin/board.exe