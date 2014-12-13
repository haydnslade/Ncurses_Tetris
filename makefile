all: link

debug:
	g++ -g -o debugTetris main.cpp game.cpp playArea.cpp block.cpp blockTypes.cpp -lncurses -std=c++11

compile:
	g++ -c main.cpp -std=c++11
	g++ -c game.cpp -std=c++11
	g++ -c playArea.cpp -std=c++11
	g++ -c block.cpp -std=c++11
	g++ -c blockTypes.cpp -std=c++11

link:compile
	g++ -o tetris main.o game.o playArea.o block.o blockTypes.o -lncurses

clean:
	rm -f tetris *.o
