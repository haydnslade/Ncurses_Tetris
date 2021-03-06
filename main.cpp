/* Copyright 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <string>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include "game.h"
using namespace std;

const int EASY_GAME = 1;
const int MED_GAME = 25;
const int HARD_GAME = 50;

/* Signal handler for proper exit */
void exitProper(int sigNum);
 
int main(void) {
  int row,col;
  initscr();
  signal(SIGINT, exitProper);
  getmaxyx(stdscr,row,col);//get screen size
  start_color();//start color mode
  init_pair(1, COLOR_GREEN, COLOR_RED);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1)|A_BOLD|A_UNDERLINE);
  string title="Tetris";
  string option1="1.Easy:Slow/Boring";
  string option2="2.Normal:Moderate/Fun";
  string option3="3.Hard:Insane/Frustrating";
  mvprintw(5,(col/2)-(title.length()/2),"%s",title.c_str()); 
  standend();
  attron(COLOR_PAIR(2));
  mvprintw(10,(col/2)-(option1.length()/2),"%s",option1.c_str()); 
  standend();
  attron(COLOR_PAIR(3));
  mvprintw(12,(col/2)-(option2.length()/2),"%s",option2.c_str());
  standend();
  attron(COLOR_PAIR(4));
  mvprintw(14,(col/2)-(option3.length()/2),"%s",option3.c_str());
  standend();//get rid of attributes
  cbreak();// direct inout
  string selection="Please Select your game:";
  string error="Please eneter a # 1-3 or q to quite.";
  mvprintw(18,(col/2)-(selection.length()/2),"%s",selection.c_str());
  char input;
  Game * newGame;
  while((input=getch())!='q')
  {
    switch(input) {
      case '1':
        clear();
        newGame = new Game(EASY_GAME);
        break;
      case '2':
        clear();
        newGame = new Game(MED_GAME);
        break;
      case '3':
        clear();
        newGame = new Game(HARD_GAME);
        break;
      default:
        mvprintw(20,(col/2)-(selection.length()/2),"Enter 1,2,3 or q to quite");
        move(18,(col/2)+(selection.length()/2));
        break;
    }
    if(input=='1'||input=='2'||input=='3') {
        newGame->runGame();
      break;
    }
  }
  
  
  refresh();
  //getch(); // pauses screen
  endwin();
}

void exitProper(int sigNum) {
    endwin();
    exit(sigNum);
}
