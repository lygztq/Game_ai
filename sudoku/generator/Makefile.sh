g++ -Wall --std=c++11 -c constant.cpp -o constant.o
g++ -Wall --std=c++11 -c random.cpp -o random.o
g++ -Wall --std=c++11 -c sudoku_server.cpp -o sudoku_server.o
g++ -Wall --std=c++11 -c sudoku_generator.cpp -o sudoku_generator.o
g++ -Wall --std=c++11 -c test.cpp -o test.o
g++ -Wall --std=c++11 -c instance_reader.cpp -o instance_reader.o
g++ instance_reader.o constant.o random.o sudoku_server.o sudoku_generator.o test.o -o test.exe




