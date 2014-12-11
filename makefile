all:
	g++ main.cpp game.cpp playArea.cpp block.cpp -o app -lncurses -std=c++11
make:
	g++ main.cpp -o app -lncurses -std=c++11
