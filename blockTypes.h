/* Copyright 2014 Haydn Slade
 * This program was designed and written by Haydn Slade
 * No code in this file was copied directly from any other source
 * and was written by me (while being influenced by outside sources.)
 */

#ifndef BLOCK_TYPES
#define BLOCK_TYPES

const int NUM_BLK_TYPES = 7;
const int NUM_BLK_ORNT = 4;
const int BLK_SIZE = 5;

/*
 * Block definitions, simply use an array of bytes to store the different
 * blocks, and their rotations. Found this idea at http://javilop.com/gamedev/
 */
char blockTypesAndRotations [NUM_BLK_TYPES][NUM_BLK_ORNT][BLK_SIZE][BLK_SIZE]
{
    // Square
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
        },
        {
        },
        {
        }
    },
    // Line
    {
    },
    // L
    {
    },
    // Backwards L
    {
    },
    // Zigzag
    {
    },
    // Backwards Zigzag
    {
    },
    // T
    {
    }
};

#endif
