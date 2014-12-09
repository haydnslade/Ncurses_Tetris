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

Game::runGame() {

}

Block * Game::createNewPiece(int startX, int startY) {

}

Game::drawBoard() {

}

Game::drawBlock(Block * blockToDraw) {

}

Game::drawScore() {

}

int Game:getRandBlockType() {

}
