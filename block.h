/* Copyright 2014 Haydn Slade
 * This program was designed and written by Haydn Slade                         
 * No code in this file was copied directly from any other source               
 * and was written by me (while being influenced by outside sources.)           
 */    

#ifndef BLOCK_PIECE
#define BLOCK_PIECE

#include "blockTypes.h"

/*
 * Block
 * Block Object containing data about a block, including position and color
 * TODO Include in depth comments
 */
class Block {
    private:
        // Type and orientation of the block
        int blkType, blkOrnt;
        // What color to display
        int blkColor;
        // Current position
        int curX, curY;

    public:
        // Default constructor
        Block();
        // Destructor
        ~Block();
        // Parameterized with type, color, and pos
        Block(int blkType, int blkColor, int startX, int startY);

        // Move the block specified x value
        void moveBlockX(int x);
        // Move the block specified y value
        void moveBlockY(int y);
        // Get the current block x position
        int getX(void);
        // Get the current block y position
        int getY(void);
        // Get the block type
        int getBlockType(void);
        // Get the block orientation
        int getBlockOrient(void);
        // Get the block color
        int getBlockColor(void);
};

#endif
