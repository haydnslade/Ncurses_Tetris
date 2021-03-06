/* Copyright 2014 Haydn Slade
 * This program was designed and written by Haydn Slade                         
 * No code in this file was copied directly from any other source               
 * and was written by me (while being influenced by outside sources.)           
 */

#ifndef TETRIS_GAME
#define TETRIS_GAME

#include <ncurses.h>

#include "block.h"
#include "blockTypes.h"
#include "playArea.h"

#define IN_PLAY_BLK 1
#define FUTURE_BLK 0

const int WINDOW_LINES = 25;
const int WINDOW_COLS = 50;
const int WAIT_TIME = 750;
const int LEFT_OFFSET = 5;
const int TOP_OFFSET = 5;
const int SCORE_MOD = 10;
const int LINES_P_LVL = 5;
const int MILLI_SEC = 1000;
const int TIME_MOD = 25;
const int CLR_PAIR_OFFSET = 10;

/*
 * Game()
 * Handles all functions for the game itself, including drawing the board and
 * pieces on the screen, as well as the main game loop.
 */
class Game {
    private:
        Block * blkInPlay;
        Block * nextBlk;
        PlayArea * gameArea;

        WINDOW * gameWin;
        
        int currentLevel, currentScore, linesRemoved;

    public:
        Game();
        Game(int startLvl);
        ~Game();

        void runGame(void);
        Block * createNewPiece(int startX, int startY, int type);

    private:
        void drawBoard(void);
        void drawBlock(Block * blockToDraw);
        void drawScore(void);
        void endGame(void);
        int getRandBlockType(void);
};

#endif
