#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cube.h"

cubeCalc *cube_init()
{
    //cube_xyz_set(cc, x, y, z);
    cubeCalc *cc = (cubeCalc *)malloc(sizeof(cubeCalc));
    cc->x = 0;
    cc->y = 0;
    cc->z = 0;

    cc->X = 1;
    cc->Y = 1;
    cc->Z = 1;
    cube_ptr_set(cc);
    cc->cube_set_xyz = cube_set_xyz;
    cc->cube_set_x = cube_set_x;
    cc->cube_set_y = cube_set_y;
    cc->cube_set_z = cube_set_z;
    return cc;
}

void cube_ptr_set(cubeCalc *cc)
{
    //cc->ptr = (int **)malloc(sizeof(int *) * 72);
    int *x, *y, *z, *X, *Y, *Z;
    x = &cc->x;
    y = &cc->y;
    z = &cc->z;
    X = &cc->X;
    Y = &cc->Y;
    Z = &cc->Z;

    int *positions[6][12] = {
        {x, Y, Z, X, Y, Z, X, Y, z, x, Y, z},  //Top
        {x, y, z, X, y, z, X, y, Z, x, y, Z},  //Bottum
        {x, y, z, x, y, Z, x, Y, Z, x, Y, z},  //Left Maybe
        {X, y, Z, X, y, z, X, Y, z, X, Y, Z},  //Right Maybe
        {X, y, z, x, y, z, x, Y, z, X, Y, z},  //Front Maybe
        {x, y, Z, X, y, Z, X, Y, Z, x, Y, Z}}; //Back Maybe

    //bcopy(positions, cc->ptr, sizeof(positions));
    memcpy(cc->ptr, positions, sizeof(positions));
}
void cube_debug_print(cubeCalc *cc)
{
    char text[12];
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            //printf("%d,", *(cc->ptr[y][x]));
            text[x] = (*(cc->ptr[y][x])) + '0';
        }
        printf("%.*s\n", 12, text);
    }
}

void cube_set_xyz(cubeCalc *cc, int x, int y, int z)
{
    cc->x = x;
    cc->y = y;
    cc->z = z;

    cc->X = x + 1;
    cc->Y = y + 1;
    cc->Z = z + 1;
}
void cube_set_x(cubeCalc *cc, int x)
{
    cc->x = x;
    cc->X = x + 1;
}
void cube_set_y(cubeCalc *cc, int y)
{
    cc->y = y;
    cc->Y = y + 1;
}
void cube_set_z(cubeCalc *cc, int z)
{
    cc->z = z;
    cc->Z = z + 1;
}

void cube_test(int x, int y, int z)
{
    cubeCalc *cc = cube_init();
    cc->cube_set_xyz(cc, x, y, z);
    cube_debug_print(cc);
    free(cc);
}