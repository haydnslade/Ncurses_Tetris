/* Copyright 2014
 */

#include "game.h"
#include <stdlib.h>
#include <curses.h>

Game::Game() {
    currentLevel = 0;
    currentScore = 0;
    // blkInPlay = createNewPiece(?, ?);
    // nextBlk = createNewPiece(?, ?);
    gameArea = new PlayArea();
}

Game::Game(int startLvl) {
    currentLevel = startLvl;
    currentScore = 0;
    // blkInPlay = createNewPiece(?, ?);
    // nextBlk = createNewPiece(?, ?);
    gameArea = new PlayArea();
}

Game::~Game() {
    delete blkInPlay;
    delete nextBlk;
    delete gameArea;
}

void Game::runGame(void) {
    int screenX, screenY;
    printw("Game Started");
    refresh();
    getmaxyx(stdscr, screenX, screenY);
    nextGameWin = newwin(screenY, screenX, 0, 0);
    mvwaddstr(nextGameWin, 0, 0, "Test");
    currGameWin = nextGameWin;
    wrefresh(currGameWin);
    getch();
}

Block * Game::createNewPiece(int startX, int startY, int type) {
    int actX, actY;
    int blkType = this->getRandBlockType();
    int blkColor = blockColors[blkType];
    if (type == IN_PLAY_BLK) {
        actX = startX + blockStartPos[blkType][0][0];
        actY = startY + blockStartPos[blkType][0][1];
    } else {
        actX = startX;
        actX = startY;
    }
    Block * nextBlock = new Block(blkType, blkColor, actX, actY);
    return nextBlock;
}

void Game::drawBoard(void) {

}

void Game::drawBlock(Block * blockToDraw) {

}

void Game::drawScore(void) {

}

int Game::getRandBlockType(void) {
    return rand() % NUM_BLK_TYPES;
}
