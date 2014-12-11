/* Copyright 2014
 */

#include "game.h"
#include <stdlib.h>

Game::Game() {
    currentLevel = 0;
    currentScore = 0;
    blkInPlay = createNewPiece(?, ?);
    nextBlk = createNewPiece(?, ?);
    gameArea = new PlayArea;
}

Game::Game(int startLvl) {
    currentLevel = startLvl;
    currentScore = 0;
    blkInPlay = createNewPiece(?, ?);
    nextBlk = createNewPiece(?, ?);
    gameArea = new PlayArea;
}

Game::~Game() {
    delete blkInPlay;
    delete nextBlk;
    delete gameArea;
}

void Game::runGame(void) {
    printw("Game Started");
}

Block * Game::createNewPiece(int startX, int startY) {

}

void Game::drawBoard(void) {

}

void Game::drawBlock(Block * blockToDraw) {

}

void Game::drawScore(void) {

}

int Game:getRandBlockType(void) {

}
