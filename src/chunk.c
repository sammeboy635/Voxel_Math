#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "vector.h"
#include "FastNoiseLite.h"
#include "cube.h"

#include "FastNoiseLite.h"
#include "block.h"
#include "chunk.h"

Chunk *chunk_init(cubeCalc *cc, int x, int y, int z)
{
    Chunk *chunk = (Chunk *)calloc(1, sizeof(Chunk));
    chunk->pos.x = x;
    chunk->pos.y = y;
    chunk->pos.z = z;
    //chunk->verts = (Vertices *)malloc(sizeof(Vertices));
    chunk->vert.index = 0;
    chunk->vert.size = vertices_size;
    chunk->vert.vertices = (int *)malloc(chunk->vert.size * sizeofInt);
    chunk_blockmap(chunk, cc);
    return chunk;
}

void chunk_blockmap(Chunk *chunk, cubeCalc *cc)
{
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;

    int noiseY;
#pragma omp parallel for
    for (int x = 0; x < width; x++)
    {
        for (int z = 0; z < width; z++)
        {

            chunk->blockMap[x][height][z] = (int)(48 * (1 + fnlGetNoise2D(&noise, chunk->pos.x + x, chunk->pos.z + z)));
            noiseY = chunk->blockMap[x][height][z];

            /*for (int y = height - 1; y > noiseY; y--)
            {
                chunk->blockMap[x][y][z] = AIR; //air
            }*/

            chunk->blockMap[x][noiseY][z] = Grass;

            for (int y = noiseY - 1; y > 0; y--)
            {
                chunk->blockMap[x][y][z] = STONE; //stone
            }

            chunk->blockMap[x][0][z] = BEDROCK; //bedrock

            //printf("%d  ", chunk->blockMap[x][height][z]);
        }
    }
}

void chunk_create_vertices(Chunk *chunk, cubeCalc *cc)
{
    int topBlock;
#pragma omp parallel for
    for (int x = 1; x < width - 1; x++)
    {
        cc->cube_set_x(cc, x);
        for (int z = 0; z < width - 1; z++)
        {
            cc->cube_set_z(cc, z);
            topBlock = chunk->blockMap[x][height][z];
            for (int y = topBlock; y > 0; y--)
            {
                cc->cube_set_z(cc, z);
                chunk_check_air(chunk, cc);
            }
            chunk_vertices_check_size(chunk);
        }
    }
}
int chunk_check_air(Chunk *chunk, cubeCalc *cc)
{
    int X, Y, Z;
    for (int i = 0; i < 6; i++)
    {
        X = blockSides[i][0] + cc->x;
        Y = blockSides[i][1] + cc->y;
        Z = blockSides[i][2] + cc->z;
        if (chunk->blockMap[X][Y][Z] == AIR)
        {
            //printf("%d,%d,%d \n", cc->x, cc->y, cc->z);
            for (int x = 0; x < 12; x++)
            {
                chunk->vert.vertices[chunk->vert.index++] = *(cc->ptr[i][x]);
            }
        }
    }
}
int chunk_check_pos_inside(Chunk *chunk, int x, int y, int z)
{
    int X = chunk->pos.x;
    int Y = chunk->pos.y;
    int Z = chunk->pos.z;
    //Chunk pos y is stackable 0 or 256
    if (X >= x | Y >= y | Z >= z)
    {
        if (X <= x + width | Y <= y + height | Z <= z + width)
        {
            return True;
        }
    }
    return False;
}
//Needs work
int chunk_check_pos_edge(Chunk *ch, int X, int Y, int Z)
{
    int x = ch->pos.x;
    int y = ch->pos.y;
    int z = ch->pos.z;
    //Chunk pos y is stackable 0 or 256

    if (X == x)
    {
        if (Z == z)
        {
            if (Y == y)
            {
            }
            else if (Y == y + height)
            {
            }
        }
        else if (Z == z + width) //Might need to adjust value by -1
        {
            if (Y == y)
            {
            }
            else if (Y == y + height)
            {
            }
        }
    }
    else if (X == x + width)
    {
    }
    else if (Z == z)
    {
    }
    else if (Z == z + width)
    {
    }
    else if (Y == y)
    {
    }
    else if (Y == y + height - 1)
    {
    }

    return False;
}

void chunk_vertices_check_size(Chunk *chunk)
{
    if (chunk->vert.index > chunk->vert.size - sizeofCube)
    {
        chunk->vert.size += vertices_size;
        chunk->vert.vertices = (int *)realloc(chunk->vert.vertices, chunk->vert.size * sizeofInt);
        if (chunk->vert.vertices == NULL)
        {
            printf("Error in Chunk_vertices\n");
            exit(0);
        }
    }
}
void chunk_test()
{
    cubeCalc *cc = cube_init();
    Chunk *chunk = chunk_init(cc, 0, 0, 0);
    chunk_create_vertices(chunk, cc);
    printf("%d, %d", chunk->vert.size, chunk->vert.index);
}