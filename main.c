#include <stdio.h>
#include <stdlib.h>
#include "headers/BufferUtility.h"
int main()
{
    char* file1 = 'file1.csv';
    char* file2 = 'file2.csv';

    printf("Hello world!\n");

    createBuffer();



    struct Tupla* tuplas1 = readTuplas(file1);

    struct Tupla* tuplas2 = readTuplas(file2);


    return 0;
}
