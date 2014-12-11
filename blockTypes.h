/* Copyright 2014
 */

#ifndef BLOCK_TYPES_H
#define BLOCK_TYPES_H

const int NUM_BLK_TYPES = 7;
const int NUM_BLK_ORNT = 4;
const int BLK_SIZE = 5;
const int DIMENSIONS = 2;

extern const char blockTypesAndRotations [NUM_BLK_TYPES][NUM_BLK_ORNT][BLK_SIZE][BLK_SIZE];
extern const int blockStartPos [NUM_BLK_TYPES][NUM_BLK_ORNT][DIMENSIONS];
extern const int blockColors[NUM_BLK_TYPES];

#endif
