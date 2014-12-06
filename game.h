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
 *
 */
class Game {
    private:
        Block * blkInPlay;
        Block * nextBlk;
        PlayArea * gameArea;

        Window * gameWin;
        
        int currentLevel, currentScore;

    public:
        Game();
        ~Game();

        void renderGame();
        Block * createNewPiece();

    private:
        void drawBoard();
        void drawBlock(Block blockToDraw);
        void drawScore();
        int getRandBlocktype();
};

#endif
