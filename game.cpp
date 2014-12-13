/* Copyright 2014
 */

#include "game.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>

Game::Game() {
    srand(time(NULL));
    currentLevel = 0;
    currentScore = 0;
    blkInPlay = createNewPiece(((AREA_WIDTH + 1) / 2) , 0, IN_PLAY_BLK);
    nextBlk = createNewPiece(AREA_WIDTH + 1, 0, FUTURE_BLK);
    gameArea = new PlayArea();
}

Game::Game(int startLvl) {
    srand(time(NULL));
    currentLevel = startLvl;
    currentScore = 0;
    blkInPlay = createNewPiece(((AREA_WIDTH + 1) / 2) , 0, IN_PLAY_BLK);
    nextBlk = createNewPiece(AREA_WIDTH + 1, 0, FUTURE_BLK);
    gameArea = new PlayArea();
}

Game::~Game() {
    delete blkInPlay;
    delete nextBlk;
    delete gameArea;
}

void Game::runGame(void) {
    int screenX, screenY;
    getmaxyx(stdscr, screenX, screenY);
    gameWin = newwin(screenX, screenY, 0, 0);
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    // Initialize clock to handle when to move down
    clock_t start = clock();
    while (1) {
        //usleep(WAIT_TIME * 10);
        //nextGameWin = newwin(screenX, screenY, 0, 0);
        werase(gameWin);
        // Draw the board, blocks, and score
        drawBoard();
        drawBlock(blkInPlay);
        drawBlock(nextBlk);
        drawScore();
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

                currentLevel = (currentScore / 50) + 1;
                
                if (gameArea->areaFilled()) {
                    endGame();
                    return;
                }

                blkInPlay = nextBlk;
                /* Move the block to the correct start pos */
                blkInPlay->moveBlockX(-(blkInPlay->getX())
                    + ((AREA_WIDTH + 1) / 2)
                    + blockStartPos[blkInPlay->getBlockType()][0][0]);
                blkInPlay->moveBlockY(-(blkInPlay->getY())
                    + blockStartPos[blkInPlay->getBlockType()][0][1]);

                nextBlk = createNewPiece(AREA_WIDTH + 1, 0, FUTURE_BLK);
                break;
            }
        }
        clock_t end = clock();
        clock_t elapsedTicks = (end - start);
        double elapsedSecs = elapsedTicks / (double) CLOCKS_PER_SEC;
        
        if ((elapsedSecs * 1000) >= (WAIT_TIME - (currentLevel * 25))) {
            if (gameArea->validBlockMove(blkInPlay, 0, 1)) {
                blkInPlay->moveBlockY(1);
            } else {
                gameArea->storeBlock(blkInPlay);
                currentScore += (gameArea->removeFilledLines()) * 10 * currentLevel;

                currentLevel = (currentScore / 50) + 1;

                if (gameArea->areaFilled()) {
                    endGame();
                    return;
                }

                blkInPlay = nextBlk;
                blkInPlay->moveBlockX(-(blkInPlay->getX())
                    + ((AREA_WIDTH + 1) / 2)
                    + blockStartPos[blkInPlay->getBlockType()][0][0]);
                blkInPlay->moveBlockY(-(blkInPlay->getY())
                    + blockStartPos[blkInPlay->getBlockType()][0][1]);

                nextBlk = createNewPiece(AREA_WIDTH + 1, 0, FUTURE_BLK);
            }
            start = clock();
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
    // Print the border
    mvwhline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET, '=', AREA_WIDTH);
    mvwhline(gameWin, TOP_OFFSET + AREA_HEIGHT, LEFT_OFFSET, '=', AREA_WIDTH);
    mvwvline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET - 1, '|', AREA_HEIGHT + 2);
    mvwvline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET + AREA_WIDTH, '|', AREA_HEIGHT + 2);

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
    mvwhline(gameWin, TOP_OFFSET + BLK_SIZE, LEFT_OFFSET + AREA_WIDTH + 1, '=', BLK_SIZE);
    mvwvline(gameWin, TOP_OFFSET - 1, LEFT_OFFSET + AREA_WIDTH + BLK_SIZE, '|', BLK_SIZE + 1);
    mvwprintw(gameWin, TOP_OFFSET + BLK_SIZE + 2, LEFT_OFFSET + AREA_WIDTH + 1, "Level: %d", currentLevel);
    mvwprintw(gameWin, TOP_OFFSET + BLK_SIZE + 3, LEFT_OFFSET + AREA_WIDTH + 1, "Score: %d", currentScore);
}

void Game::endGame(void) {
    curs_set(1);
    echo();
    nodelay(stdscr, false);
    mvwaddstr(gameWin, TOP_OFFSET + (AREA_HEIGHT / 2), LEFT_OFFSET, "GAME OVER");
    wrefresh(gameWin);
    getch();
    werase(gameWin);
    wrefresh(gameWin);
    delwin(gameWin);
}

int Game::getRandBlockType(void) {
    return rand() % NUM_BLK_TYPES;
}
