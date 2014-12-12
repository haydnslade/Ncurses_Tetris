/* Copyright 2014
 */

#include "game.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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
    srand(time(NULL));
    getmaxyx(stdscr, screenX, screenY);
    gameWin = newwin(screenX, screenY, 0, 0);
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    //clearok(gameWin, true);
    while (1) {
        //usleep(WAIT_TIME * 10);
        //nextGameWin = newwin(screenX, screenY, 0, 0);
        werase(gameWin);
        drawBoard();
        drawBlock(blkInPlay);
        drawBlock(nextBlk);
        /* create a temp window for the now outdated window
         * then erase the outdated (currently showing) refresh and delete
         * then refresh the screen with the now updated window state in next
         */
        /*WINDOW * oldWin = currGameWin;
        currGameWin = nextGameWin;
        werase(oldWin);
        wrefresh(oldWin);
        delwin(oldWin);
        wrefresh(currGameWin);
        nodelay(currGameWin, true);
        keypad(currGameWin, true);
        */
        wrefresh(gameWin);
        /* Get the input from user, if there is any */
        int in = getch();
        switch (in) {
            case KEY_LEFT: {
                if (gameArea->validBlockMove(blkInPlay, -1, 0))
                    blkInPlay->moveBlockX(-1);
                break;
            }
            case KEY_RIGHT: {
                if (gameArea->validBlockMove(blkInPlay, 1, 0))
                    blkInPlay->moveBlockX(1);
                break;
            }
            case KEY_UP: {
                int nextOrient = blkInPlay->getBlockOrient() + 1;
                if (gameArea->validBlockMove(blkInPlay, 0, 0, nextOrient))
                    blkInPlay->rotateBlock();
                break;
            }
            case KEY_DOWN: {
                // Move the block down until it can't move down
                while (gameArea->validBlockMove(blkInPlay, 0, 1)) {
                    blkInPlay->moveBlockY(1);
                }
                
                gameArea->storeBlock(blkInPlay);
                currentScore += (gameArea->removeFilledLines()) * 10 * currentLevel;
                
                if (gameArea->areaFilled()) {
                    getch();
                    exit(0);
                }

                blkInPlay = nextBlk;
                /* Move the block to the correct start pos */
                blkInPlay->moveBlockX(-(blkInPlay->getX())
                    + ((AREA_WIDTH + 1) / 2)
                    + blockStartPos[blkInPlay->getBlockType()][0][0]);
                blkInPlay->moveBlockY(-(blkInPlay->getY())
                    + blockStartPos[blkInPlay->getBlockType()][0][1]);

                nextBlk = createNewPiece(AREA_WIDTH + 6, 0, FUTURE_BLK);
                break;
            }
        }
        
    }
}

Block * Game::createNewPiece(int startX, int startY, int type) {
    int actX, actY;
    int blkType = getRandBlockType();
    int blkColor = blockColors[blkType];
    if (type == IN_PLAY_BLK) {
        actX = startX +  blockStartPos[blkType][0][0];
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
    /*
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
    */
    // Print the border
    mvwhline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET, '=', AREA_WIDTH + 1);
    mvwhline(gameWin, TOP_OFFSET + AREA_HEIGHT, LEFT_OFFSET, '=', AREA_WIDTH + 1);
    mvwvline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET - 1, '|', AREA_HEIGHT + 2);
    mvwvline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET + AREA_WIDTH + 1, '|', AREA_HEIGHT + 2);

    // Print board
    for (int y = 0; y < AREA_HEIGHT; y++) {
        for (int x = 0; x < AREA_WIDTH; x++) {
            int boardFill = gameArea->getFillAtPos(x, y);
            wattron(gameWin, COLOR_PAIR(boardFill + 10));
            mvwaddch(gameWin, y + TOP_OFFSET, x + LEFT_OFFSET, '*');
            wattroff(gameWin, COLOR_PAIR(boardFill + 10));
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
                wattron(gameWin, COLOR_PAIR(blkColor + 10));
                mvwaddch(gameWin, blkY + y + TOP_OFFSET, blkX + x + LEFT_OFFSET, '*');
                wattroff(gameWin, COLOR_PAIR(blkColor + 10));
            }
        }
    }
}

void Game::drawScore(void) {
    int midScreen = LINES / 3;
}

void Game::endGame(void) {
    
}

int Game::getRandBlockType(void) {
    return rand() % NUM_BLK_TYPES;
}
