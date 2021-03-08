#ifndef CHUNK_H
#define CHUNK_H

#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include "block.h"
#include "vector.h"
#include "cube.h"

#define width 32
#define height 256
#define array_height 257

#define Top 1
#define Bottom 2
#define North 3
#define South 4
#define West 5
#define East 6

#define Top_North 7
#define Top_South 8
#define Top_East 9
#define Top_West 10

#define Bottum_North 11
#define Bottum_South 12
#define Bottum_East 13
#define Bottum_West 14

#define North_East 15
#define North_West 16
#define South_East 17
#define South_West 18

#define sizeofInt 4
#define sizeofCube 72
#define vertices_size width *width * 2

typedef struct vertices
{
    int index;
    int size;
    int *vertices;
} Vertices;

typedef struct chunk
{
    Vec3 pos;
    Vertices vert;
    //int index;
    //int size;
    //int *vertices;
    int blockMap[width][array_height][width];

} Chunk;

Chunk *chunk_init(cubeCalc *cc, int x, int y, int z);
void chunk_blockmap(Chunk *chunk, cubeCalc *cc);
int chunk_check_air(Chunk *chunk, cubeCalc *cc);

int chunk_vertices_init(Vertices *verts);
void chunk_vertices_check_size(Chunk *verts);

void chunk_test();
#endif