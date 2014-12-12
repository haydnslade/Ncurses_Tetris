/* Copyright 2014
 */

#include "block.h"
#include <stdlib.h>

Block::Block() {
    blkType = 0;
    blkOrnt = 0;
    blkColor = 1;
    curX = 0;
    curY = 0;
}

Block::Block(int blockType, int blockColor, int startX, int startY) {
    blkType = blockType;
    blkOrnt = 0;
    blkColor = blockColor;
    curX = startX;
    curY = startY;
}

Block::~Block() {

}

void Block::moveBlockX(int x) {
    curX += x;
}

void Block::moveBlockY(int y) {
    curY += y;
}

void Block::rotateBlock(void) {
    blkOrnt = ((blkOrnt + 1) % NUM_BLK_ORNT);
}

int Block::getX(void) {
    return curX;
}

int Block::getY(void) {
    return curY;
}

int Block::getBlockType(void) {
    return blkType;
}

int Block::getBlockOrient(void) {
    return blkOrnt;
}

int Block::getBlockColor(void) {
    return blkColor;
}
