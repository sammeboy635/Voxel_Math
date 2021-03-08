#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cube.h"
#include "chunk.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Dynamic_Array
{
    void *ptr;
    int index;
    int size;
} Dynamic_Array;

Dynamic_Array *dyn_init(int sizeOfElem, int length)
{
    Dynamic_Array *self = (Dynamic_Array *)malloc(sizeof(Dynamic_Array));
    self->ptr = (void *)malloc(sizeOfElem * length);
    self->size = length;
    self->index = 0;
}

void func_fill(void *ptr, int length, int value)
{
    int *arr = (int *)ptr;

    for (int i = 0; i < length; i++)
    {
        arr[i] = value;
    }
}

void func_print(void *ptr, void *value)
{
    int *arr = (int *)ptr;
    for (int i = 0; i < value; i++)
    {
        printf("%d", arr[i]);
    }
}

void main()
{
    Dynamic_Array *self = dyn_init(sizeof(int), 100);
    func_fill(self->ptr, self->size, 5);
    func_print(self->ptr, self->size);
    //cube_init(cc, 0, 0, 0);

    //TICK(timeb);
    //printf("%d", *(cc->ptr[0][0]));
    //chunk_test();
    /*short blockMap[32][257][32];
    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 257; y++)
        {
            for (int z = 0; z < 32; z++)
            {
                blockMap[x][y][z] = 0;
            }
        }
    }*/
    //TOCK(timeb);
    //printf("");
}