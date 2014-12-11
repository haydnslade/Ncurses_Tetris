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
    
    /* Loop through the block array and the corresponding position in the board
     * array for the block array. Then check if any filled point in the block
     * array is outside the board limits or touching a position already filled
     */
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

int PlayArea::removeFilledLines(void) {
    int removedLines = 0;
    // Loop through every row & col, for each row if all cols are filled delete
    for (int i = 0; i < AREA_HEIGHT; i++) {
        int filledBlks = 0;
        for (int j = 0; j < AREA_WIDTH; j++) {
            if (blocksInPlay[j][i] != 0) {
                filledBlks++;
            }
        }
        // Check if the current row has every col filled, if so then delete
        if (filledBlks == AREA_WIDTH) {
            removeLine(i);
            removedLines++;
        }
    }

    return removedLines;
}

void PlayArea::storeBlock(Block * blkToStore) {
    int blkType = blkToStore->getBlockType();
    int blkOrient = blkToStore->getBlockOrient();
    for (int i = 0, nextBlkX = blkToStore->getX(); i < BLK_SIZE; i++,
            nextBlkX++) {
        for (int j = 0, nextBlkY = blkToStore->getY(); j < BLK_SIZE; j++,
                nextBlkY++) {
            if (blockTypesAndRotations[blkType][blkOrient][i][j] != 0) {
                blocksInPlay[nextBlkX][nextBlkY] = blkToStore->getBlockColor();
            }
        }
    }
}

bool PlayArea::areaFilled(void) {
    for (int i = 0; i < AREA_WIDTH; i++) {
        // If any block in top row then game over
        if (blocksInPlay[i][0] != 0) {
            return true;
        }
    }

    return false;
}

void PlayArea::initArea(void) {
    for (int i = 0; i < AREA_HEIGHT; i++) {
        for (int j = 0; j < AREA_WIDTH; j++) {
            blocksInPlay[i][j] = 0;
        }
    }
}

void PlayArea::removeLine(int lineNum) {
    // Check the row provided and all rows above
    for (int y = lineNum; y > 0; y--) {
        for (int x = 0; x < AREA_WIDTH; x++) {
            blocksInPlay[x][y] = blocksInPlay[x][y - 1];
        }
    }
}
