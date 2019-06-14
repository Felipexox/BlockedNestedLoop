#include <stdio.h>
#include <stdlib.h>
#include "headers/BufferUtility.h"
int main()
{
    int tamBuffer = 10;

    int tPagina = 2;

    // char* fileName1 = 'file1.txt';
    FILE* f1 = fopen("file1.txt", "r");
    int file1Size = fileSize(f1);
    FILE* f2 = fopen("file2.txt", "r");
    // char* fileName2 = 'file2.txt';
    int file2Size = fileSize(f2);

    FILE* file1 = fopen("file1.txt", "r");

    FILE* file2 = fopen("file2.txt", "r");

    // struct Tupla* tuplas1 = readTuplas(file1); isso dava erro pq readTuplas nao ta definida

    // struct Tupla* tuplas2 = readTuplas(file2);



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

    // printf("\n Init buffer externo\n");
    // initBuffer(externo, sizeExterno, tPagina); # faltam argumentos aqui

    // printf("\n Print buffer externo\n");
    // printRegister(externo, 20, 2);


    struct Buffer* interno =  (struct Buffer*)malloc(sizeof(struct Buffer));

    printf("\nCreating buffer interno\n");
    createBuffer(interno, sizeInterno, tPagina);

    // printf("\n Init buffer interno\n");
    // initBuffer(interno, sizeInterno, tPagina);

    // printf("\n Print buffer interno\n");
    // printRegister(interno, 20, 1);
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
    int i = 0;
    int j = 0;
    for(i = 0; i < file1Size; i+= tFactor){
        initBuffer(externo, file1, i, file1Size, sizeExterno, tPagina);
        for(j = 0; j < file2Size; j+= tFactor){
            initBuffer(interno, file2, j, file2Size, sizeInterno, tPagina);
            join(externo, interno, sizeExterno, sizeInterno, tPagina);
        }
        clearBuffer(externo, sizeExterno);
        clearBuffer(interno, sizeInterno);
    }



    return 0;
}
