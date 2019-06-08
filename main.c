#include <stdio.h>
#include <stdlib.h>
#include "headers/BufferUtility.h"
int main()
{
    int tamBuffer = 24;

    int tPagina = 2;

    char* file1 = 'file1.csv';
    char* file2 = 'file2.csv';

    struct Tupla* tuplas1 = readTuplas(file1);

    struct Tupla* tuplas2 = readTuplas(file2);



    /// Tupla: 3 bites
    /// Paginas: 2 mb
    /// Buffer: 10 mb
    /// Buffer page factor: 5
    /// Externo: 3
    /// Interno: 2

   // int bufferPageFac = bufferPageFactor(tamBuffer, tPagina);

    int sizeInterno = 2;

    int sizeExterno = 3;


   /// int pageS = blockingFactor(tPagina * MEGA, sizeof(struct Tupla));

    struct Buffer* externo = (struct Buffer*)malloc(sizeof(struct Buffer));
    printf("\nCreating buffer externo\n");
    createBuffer(externo, sizeExterno, tPagina);

    printf("\n Init buffer externo\n");
    initBuffer(externo, sizeExterno, tPagina);

    printf("\n Print buffer externo\n");
    printRegister(externo, 20, 1);

   // struct Buffer* interno;

    //createBuffer(interno, sizeInterno, tPagina);



    return 0;
}
