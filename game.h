/* Copyright 2014 Haydn Slade
 * This program was designed and written by Haydn Slade                         
 * No code in this file was copied directly from any other source               
 * and was written by me (while being influenced by outside sources.)           
 */

#ifndef TETRIS_GAME
#define TETRIS_GAME

#include <curses.h>

#include "block.h"
#include "playArea.h"

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

        WINDOW * currGameWin;
        WINDOW * nextGameWin;
        
        int currentLevel, currentScore;

    public:
        Game();
        Game(int startLvl);
        ~Game();

        void runGame(void);
        Block * createNewPiece(int startX, int startY);

    private:
        void drawBoard(void);
        void drawBlock(Block * blockToDraw);
        void drawScore(void);
        int getRandBlockType(void);
};

#endif
