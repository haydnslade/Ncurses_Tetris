/* Copyright 2014
 */

#include "game.h"
#include <stdlib.h>
#include <curses.h>

Game::Game() {
    currentLevel = 0;
    currentScore = 0;
    blkInPlay = createNewPiece(((AREA_WIDTH + 1) / 2) , 0, IN_PLAY_BLK);
    nextBlk = createNewPiece(AREA_WIDTH + 6, 0, FUTURE_BLK);
    gameArea = new PlayArea();
}

Game::Game(int startLvl) {
    currentLevel = startLvl;
    currentScore = 0;
    blkInPlay = createNewPiece(((AREA_WIDTH + 1) / 2) , 0, IN_PLAY_BLK);
    nextBlk = createNewPiece(AREA_WIDTH + 6, 0, FUTURE_BLK);
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
    curs_set(0);
    nextGameWin = newwin(screenX, screenY, 0, 0);
    drawBoard();
    drawBlock(blkInPlay);
    drawBlock(nextBlk);
    currGameWin = nextGameWin;
    wrefresh(currGameWin);
    getch();
    werase(currGameWin);
    wrefresh(currGameWin);
    delwin(currGameWin);
}

Block * Game::createNewPiece(int startX, int startY, int type) {
    int actX, actY;
    int blkType = getRandBlockType();
    int blkColor = blockColors[blkType];
    if (type == IN_PLAY_BLK) {
        actX = startX + blockStartPos[blkType][0][0];
        actY = startY + blockStartPos[blkType][0][1];
    } else {
        actX = startX;
        actY = startY;
    }
    Block * nextBlock = new Block(blkType, blkColor, actX, actY);
    return nextBlock;
}

void Game::drawBoard(void) {
    int midScreen = LINES / 3;
    int lBound = midScreen - AREA_WIDTH - 1;
    int rBound = midScreen + AREA_WIDTH + 1;
    int bBound = AREA_HEIGHT + 1;

    for (int y = 0; y < AREA_HEIGHT + 1; y++) {
        for (int x = 0; x < AREA_WIDTH + 2; x++) {
            if (x == 0 || x == AREA_WIDTH + 1) {
                mvwaddch(nextGameWin, y, x, '|'); 
            } else if (y == AREA_HEIGHT) {
                mvwaddch(nextGameWin, y, x, '_');
            } else {
                int boardFill = gameArea->getFillAtPos(x - 1, y);
                init_pair(boardFill + 10, boardFill, boardFill);
                wattron(nextGameWin, COLOR_PAIR(boardFill + 10));
                mvwaddch(nextGameWin, y, x, '*');
                wattroff(nextGameWin, COLOR_PAIR(boardFill + 10));
            }
        }
    }
}

void Game::drawBlock(Block * blockToDraw) {
    int blkX = blockToDraw->getX();
    int blkY = blockToDraw->getY();
    int blkColor = blockToDraw->getBlockColor();
    int blkType = blockToDraw->getBlockType();
    int blkOrient = blockToDraw->getBlockOrient();

    for (int y = 0; y < BLK_SIZE; y++) {
        for (int x = 0; x < BLK_SIZE; x++) {
            if (blockTypesAndRotations[blkType][blkOrient][x][y] != 0) {
                init_pair(blkColor + 10, blkColor, blkColor);
                wattron(nextGameWin, COLOR_PAIR(blkColor + 10));
                mvwaddch(nextGameWin, blkY + y, blkX + x, '*');
                wattroff(nextGameWin, COLOR_PAIR(blkColor + 10));
            }
        }
    }
}

void Game::drawScore(void) {
    int midScreen = LINES / 3;
}

int Game::getRandBlockType(void) {
    return rand() % NUM_BLK_TYPES;
}
