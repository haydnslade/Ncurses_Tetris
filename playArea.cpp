/* Copyright 2014
 */

#include "playArea.h"
#include <stdlib.h>

PlayArea::PlayArea() {
    initArea();
}

PlayArea::~PlayArea() {

}

bool PlayArea::validBlockMove(Block * blkMoving, int x, int y) {
    int blkCurX = blkMoving->getX();
    int blkCurY = blkMoving->getY();
    int blkNextX = blkCurX + x;
    int blkNextY = blkCurY + y;
    int blkType = blkMoving->getBlockType();
    int blkOrient = blkMoving->getBlockOrient();
    
    for (int i = 0, nextXPos = blkNextX; i < BLK_SIZE; i++, nextXPos++) {
        for (int j = 0, nextYPos = blkNextY; j < BLK_SIZE; j++, nextYPos) {
            // Check if the current pos in the block array is outside bounds
            if (nextXPos < 0 || nextXPos > AREA_WIDTH - 1
                || nextYPos > AREA_HEIGHT - 1) {
                if (blockTypesAndRotations[blkType][blkOrient][i][j] != 0) {
                    return false;
                }
            }

            /* Check if the current pos in the block array collides with stored
             * value in the Area array
             */
            if (nextYPos >= 0) {
                if ((blockTypesAndRotations[blkType][blkOrient][i][j] != 0)
                    && getFillAtPos(nextXPos, nextYPos) != 0) {
                    return false;
                }
            }
        }
    }

    // Not outside bounds & no collision
    return true;
}

int PlayArea::getFillAtPos(int x, int y) {
    return blocksInPlay[x][y];
}

int PlayArea::removeFilledLines() {

}

void PlayArea::storeBlock(Block blkToStore) {

}

bool PlayArea::areaFilled() {

}

void PlayArea::initArea() {

}

void PlayArea::removeLine(int lineNum) {

}
