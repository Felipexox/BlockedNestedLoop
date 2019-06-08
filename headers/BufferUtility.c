#include "BufferUtility.h"
#include <math.h>
#include <stdlib.h>

#define KILOBYTE 1024

void createBuffer(struct Buffer* buffer, int bufferSize, int tPagina){
    int i = 0;
    buffer->paginas = (struct Pagina*)malloc(bufferSize * sizeof(struct Pagina));

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));

    printf("\n %d \n", tFactor);

    for(i = 0; i < bufferSize; i++){
         buffer->paginas[i].tuplas = (struct Tupla*)malloc(tFactor);
    }

};

void initBuffer(struct Buffer* buffer, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
    int i = 0;
    int j = 0;
    int id = 0;
    for(i = 0; i < bufferSize; i++){
         for(j = 0; j < tFactor / sizeof(struct Tupla); j++){

            buffer->paginas[i].tuplas[j].id = id;

           // printf("%d ,", buffer->paginas[i].tuplas[j].id);
           // buffer->paginas[i].tuplas[j].cpf = 'cpf';
           // buffer->paginas[i].tuplas[j].nome = 'nome';
            id++;
         }
         printf("\n");
    }
}
void printRegister(struct Buffer* buffer, int registerSize, int tPagina){
    int i = 0;
    int j = 0;
    int id = 0;
    printf("Registros pagina %d\n", tPagina);
    for(j = 0; j < registerSize; j++){
        printf( "%d \n", buffer->paginas[tPagina].tuplas[j].id);
    //           buffer->paginas[tPagina].tuplas[j].cpf,
     //          buffer->paginas[tPagina].tuplas[j].nome);
    }

}

struct Tupla* readTuplas(char* fileName){}

int countRegisters(char* fileName){}

int amountPages(int bufferSize, int pagesSize){}

int bufferSize(struct Buffer* buffer){}

int pageSize(int blockingFactor){
    return ceil((sizeof(struct Tupla) * blockingFactor));
}

int bufferPageFactor(int bufferSize, int pageSize){
    return ceil((bufferSize/pageSize));
}

int blockingFactor(int pageSize, int regSize){
    return ceil(((pageSize * KILOBYTE * KILOBYTE)/regSize));
}
