#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KILOBYTE 1024

struct Tupla1{
    int id;
    char firstName[45];
    char lastName[45];
    int age;
    char city[45];
    char state[45];
    int zipCode;
    int idCity;
};

struct Tupla2{
    int id;
    char street[45];
    int zipCode;
};

struct Pagina1{
    struct Tupla1* tuplas;
};

struct Pagina2{
    struct Tupla2* tuplas;
};

struct Buffer1{
    struct Pagina1* paginas;
};

struct Buffer2{
    struct Pagina2* paginas;
};

/// Inicia o buffer
void createBuffer(struct Buffer1* buffer, int bufferSize, int tPagina);

int* initBuffer(struct Buffer1* buffer, FILE* file, int bufferSize, int tPagina);

void printRegister(struct Buffer1* buffer, int registerSize, int tPagina);

void createBuffer2(struct Buffer2* buffer, int bufferSize, int tPagina);

int* initBuffer2(struct Buffer2* buffer, FILE* file, int bufferSize, int tPagina);

void printRegister2(struct Buffer2* buffer, int registerSize, int tPagina);

/// Le todas as tuplas dentro do root do projeto
struct Tupla1* readTuplas(char* fileName);



int amountPages(int bufferSize, int pagesSize);

/// conta o total de registro dentro do arquivo
int countRegisters(char* fileName);

void printFileContent(char* fileName, int pAmount);

/// Cria as paginas
struct Pagina1* createPages(struct Tupla1* tuplas, int regAmount);

void clearBuffer (struct Buffer1* buffer, int pBufferSize);

void clearBuffer2 (struct Buffer2* buffer, int pBufferSize);

int readBlocking(struct Tupla1* bloco, FILE* file, int sizeToRead);

int readBlocking2(struct Tupla2* bloco, FILE* file, int sizeToRead);


/// Calcula o tamanho da pagina
int pageSize(int blockingFactor);

/// Calcula o fator de pagina do buffer
int bufferPageFactor(int bufferSize, int pageSize);

/// Calcula o fator de blocagem
int blockingFactor(int pageSize, int regSize);

void writeData(char* filename, int amountTupla);

int fileSize(FILE* file);

int qtdIndex(int tPagina,int sizeTupla);

void join(struct Buffer1* buffer1, struct Buffer2* buffer2, int tCurrentBufferPage1, int tCurrentBufferPage2, int tPagina, int deltaInterno,int deltaExterno);

int main()
{
    int tPagina = 1;
    printf("\nSize tupla1 %d\n", sizeof(struct Tupla1));
    printf("\nSize tupla2 %d\n", sizeof(struct Tupla2));
    char* fileName1 = "f1.txt";
    printf("write file 1");


    char* fileName2 = "f2.txt";
    printf("\nWrite file 2");

    FILE* file1 = fopen(fileName1, "r");

    FILE* file2 = fopen(fileName2, "r");


    /// Tupla1: 3 bites
    /// Paginas: 2 mb
    /// Buffer1: 10 mb
    /// Buffer1 page factor: 5
    /// Externo: 3
    /// Interno: 2

    int qtdInterno = 2;

    int qtdExterno = 1;

    struct Buffer1* externo = (struct Buffer1*)malloc(sizeof(struct Buffer1));

    printf("\nCreating buffer externo\n");

    createBuffer(externo, qtdExterno, tPagina);


    struct Buffer2* interno =  (struct Buffer2*)malloc(sizeof(struct Buffer2));

    printf("\nCreating buffer interno\n");

    createBuffer2(interno, qtdInterno, tPagina);

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));
    int i = 0;
    int j = 0;
    printf("\n%d",qtdIndex(tPagina,sizeof(struct Tupla1)));
    int *stateBuffer;
    int *stateBuffer2;
   do
   {
       stateBuffer = initBuffer(externo, file1, qtdExterno, tPagina);

        for(i = 0; i <=stateBuffer[0]; i++){
            do
            {
                stateBuffer2 = initBuffer2(interno, file2, qtdInterno, tPagina);
                for(j = 0; j <=stateBuffer2[0]; j++){
                    if(j != stateBuffer2[0]){
                        join(externo, interno, i, j, tPagina, qtdIndex(tPagina,sizeof(struct Tupla2)), stateBuffer[1]);
                    }else{
                        join(externo, interno, i, j, tPagina, stateBuffer2[1], stateBuffer[1]);
                    }
                }

            } while(stateBuffer2[1] == qtdIndex(tPagina,sizeof(struct Tupla2)));

            fseek(file2, 0, 0);
        }
        printf("\nFinish loop interno");
   } while (stateBuffer[1] == qtdIndex(tPagina,sizeof(struct Tupla1)));

    return 0;

}


void createBuffer(struct Buffer1* buffer, int bufferSize, int tPagina){
    int i = 0;
    buffer->paginas = (struct Pagina1*)malloc(bufferSize * sizeof(struct Pagina1));

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));

    printf("\n %d \n", tFactor);

    for(i = 0; i < bufferSize; i++){
         buffer->paginas[i].tuplas = (struct Tupla1*)malloc(tFactor);
    }

}

void createBuffer2(struct Buffer2* buffer, int bufferSize, int tPagina){
    int i = 0;
    buffer->paginas = (struct Pagina2*)malloc(bufferSize * sizeof(struct Pagina2));

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla2));

    printf("\n %d \n", tFactor);

    for(i = 0; i < bufferSize; i++){
         buffer->paginas[i].tuplas = (struct Tupla2*)malloc(tFactor);
    }

}
int qtdIndex(int tPagina,int sizeTupla)
{
    int tFactor = blockingFactor(tPagina, sizeTupla);
    return tFactor/sizeTupla;
}
int* initBuffer(struct Buffer1* buffer, FILE* file, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));
    int* seila = malloc(sizeof(int)*2);
    int i = 0;

    for(i = 0; i < bufferSize; i++){
        int stateBuffer = readBlocking(buffer->paginas[i].tuplas, file, tFactor);
        if(stateBuffer < 0){

            seila[0] = i;

            seila[1] = -stateBuffer;
            return seila;
        }
    }
    seila[0] = bufferSize - 1;
    seila[1] = tFactor/sizeof(struct Tupla1);
    return seila;

}

int* initBuffer2(struct Buffer2* buffer, FILE* file, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla2));
    int* seila = malloc(sizeof(int)*2);
    int i = 0;

    for(i = 0; i < bufferSize; i++){
        int stateBuffer = readBlocking2(buffer->paginas[i].tuplas, file, tFactor);
        if(stateBuffer < 0){
            seila[0] = i;
            seila[1] = -stateBuffer;
            return seila;
        }

    }
    seila[0] = bufferSize - 1;
    seila[1] = tFactor/sizeof(struct Tupla2);
    return seila;
}

void join(struct Buffer1* buffer1, struct Buffer2* buffer2, int tCurrentBufferPage1, int tCurrentBufferPage2, int tPagina, int deltaInterno,int deltaExterno){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));
    int tFactor2 = blockingFactor(tPagina, sizeof(struct Tupla2));


    int i = 0;
    int j = 0;

    for(i = 0; i < deltaExterno; i++){

        for(j = 0; j < deltaInterno; j++){

            if(buffer1->paginas[tCurrentBufferPage1].tuplas[i].id == buffer2->paginas[tCurrentBufferPage2].tuplas[j].id){
                printf("\n Match: %d %s %d %s ", buffer1->paginas[tCurrentBufferPage1].tuplas[i].id,buffer1->paginas[tCurrentBufferPage1].tuplas[i].city, buffer2->paginas[tCurrentBufferPage2].tuplas[j].id,buffer2->paginas[tCurrentBufferPage2].tuplas[j].street);
            }
        }
    }

}

int readBlocking(struct Tupla1* bloco, FILE* file, int sizeToRead){

    int i = 0;

    for ( i = 0; i < sizeToRead/sizeof(struct Tupla1); i++){
        if(fscanf(file, "%d %s %s %d %s %s %d %d", &bloco[i].id, (&bloco[i])->firstName, (&bloco[i])->lastName, &bloco[i].age, (&bloco[i])->city, (&bloco[i])->state, &bloco[i].zipCode, &bloco[i].idCity) == EOF){
            return -i;
        }
     }
    return (sizeToRead/sizeof(struct Tupla1));
}

int readBlocking2(struct Tupla2* bloco, FILE* file, int sizeToRead){

    int i = 0;

    for ( i = 0; i < sizeToRead/sizeof(struct Tupla2); i++){
        if(fscanf(file, "%d %s %d", &bloco[i].id,&bloco[i].street, &bloco[i].zipCode) == EOF){
            return -i;
        }
    }
    return sizeToRead/sizeof(struct Tupla2);
}

void clearBuffer (struct Buffer1* buffer, int pBufferSize){
    int i = 0;
    for(i = 0; i < pBufferSize; i++){
       free(buffer->paginas[i].tuplas);
    }
    free(buffer->paginas);
    free(buffer);
}

void clearBuffer2 (struct Buffer2* buffer, int pBufferSize){
    int i = 0;
    for(i = 0; i < pBufferSize; i++){
       free(buffer->paginas[i].tuplas);
    }
    free(buffer->paginas);
    free(buffer);
}


int pageSize(int blockingFactor){
    return ceil((sizeof(struct Tupla1) * blockingFactor));
}

int bufferPageFactor(int bufferSize, int pageSize){
    return ceil((bufferSize/pageSize));
}

int blockingFactor(int pageSize, int regSize){
    return floor(((pageSize *  KILOBYTE * KILOBYTE)/regSize));
}

