/* Copyright 2014 Haydn Slade
 * This program was designed and written by Haydn Slade                         
 * No code in this file was copied directly from any other source               
 * and was written by me (while being influenced by outside sources.)           
 */

#ifndef TETRIS_VIEW
#define TETRIS_VIEW

#include "block.h"

const int AREA_WIDTH = 10;
const int AREA_HEIGHT = 20;

/* PlayArea
 * Object that holds the play area and all methods to store pieces on the board
 * after a collision is detected as well as other methods to get blocks from
 * the board.
 * TODO In depth comments and method descriptions
 */
class PlayArea {
    private:
        // Array that holds the fallen blocks
        int blocksInPlay[AREA_WIDTH][AREA_HEIGHT];

    public:
        // Constructor
        PlayArea();
        // Destructor
        ~PlayArea();

        // Is the move valid for the block?
        bool validBlockMove(Block * blkMoving, int x, int y);
        // Get the fill at specific position
        int getFillAtPos(int x, int y);

        // Remove all filled lines, return number of lines removed
        int removeFilledLines();
        // Take a block and store it in the array
        void storeBlock(Block blkToStore);
        // Checks if blocks touched the top, aka GAMEOVEr
        bool areaFilled();

    private:
        // Initialize area to empty
        void initArea();
        // Remove a specific line and move all lines above down
        void removeLine(int lineNum);
};

#endif
