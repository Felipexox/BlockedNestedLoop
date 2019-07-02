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

void initBuffer(struct Buffer1* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina);

void printRegister(struct Buffer1* buffer, int registerSize, int tPagina);

void createBuffer2(struct Buffer2* buffer, int bufferSize, int tPagina);

void initBuffer2(struct Buffer2* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina);

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

void readBlocking(struct Tupla1* bloco, FILE* file, int sizeToRead);

void readBlocking2(struct Tupla2* bloco, FILE* file, int sizeToRead);


/// Calcula o tamanho da pagina
int pageSize(int blockingFactor);

/// Calcula o fator de pagina do buffer
int bufferPageFactor(int bufferSize, int pageSize);

/// Calcula o fator de blocagem
int blockingFactor(int pageSize, int regSize);

void writeData(char* filename, int amountTupla);

int fileSize(FILE* file);

void join(struct Buffer1* buffer1, struct Buffer2* buffer2, int tCurrentBufferPage1, int tCurrentBufferPage2, int tPagina);

int main()
{
    int tamBuffer = 24;

    int tPagina = 2;

    char* fileName1 = "f1.txt";
    printf("write file 1");
  //  writeData(fileName1, 10000000);
//    printFileContent(fileName1, 8);
    int file1Size = fileSize(fopen(fileName1, "r"));
    printf("\n File 1 Size: %d bytes", &file1Size);
    printf("\n\nWrited file 1");



    char* fileName2 = "f2.txt";
    printf("\nWrite file 2");
//    writeData(fileName2, 10000000);
    int file2Size = fileSize(fopen(fileName2, "r"));
//    printFileContent(fileName2, 7);

    printf("\n File 2 Size: %d bytes", &file2Size);
    printf("\n\nWrited file 2");

    FILE* file1 = fopen(fileName1, "r");

    FILE* file2 = fopen(fileName2, "r");


    /// Tupla1: 3 bites
    /// Paginas: 2 mb
    /// Buffer1: 10 mb
    /// Buffer1 page factor: 5
    /// Externo: 3
    /// Interno: 2

   // int bufferPageFac = bufferPageFactor(tamBuffer, tPagina);

    int qtdInterno = 2;

    int qtdExterno = 3;

   /// int pageS = blockingFactor(tPagina * MEGA, sizeof(struct Tupla1));

    struct Buffer1* externo = (struct Buffer1*)malloc(sizeof(struct Buffer1));

    printf("\nCreating buffer externo\n");

    createBuffer(externo, qtdExterno, tPagina);


    struct Buffer2* interno =  (struct Buffer2*)malloc(sizeof(struct Buffer2));

    printf("\nCreating buffer interno\n");

    createBuffer2(interno, qtdInterno, tPagina);

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));
    int i = 0;
    int j = 0;
//    for(i = 0; i < file1Size; i+= tFactor){
//        initBuffer(externo, file1, i, file1Size, sizeExterno, tPagina);
//        for(j = 0; j < file2Size; j+= tFactor){
//            initBuffer(interno, file2, j, file2Size, sizeInterno, tPagina);
//            join(externo, interno, sizeExterno, sizeInterno, tPagina);
//        }
//        clearBuffer(externo, sizeExterno);
//        clearBuffer(interno, sizeInterno);
//    }
    initBuffer(externo, file1, i, file1Size, qtdExterno, tPagina);
    initBuffer2(interno, file2, j, file2Size, qtdInterno, tPagina);
    for(i = 0; i < qtdExterno; i++){

        for(j = 0; j < qtdInterno; j++){
            join(externo, interno, i, j, tPagina);
            printf("\n\nFinish join\n\n");
        }
        printf("Clear Buffers");


    }


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

void initBuffer(struct Buffer1* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));

    int i = 0;
    //fseek(file, 0, posiInit * tFactor);

    int currentPosi = ftell(file);
    printf("\nCurrent Cursor Position in file: %d\n", &currentPosi);
    printf("\ntFactor: %d\n", tFactor);
    int delta = 0;
//    if(tFactor + currentPosi > fileSize){
//        delta = (tFactor + currentPosi) - fileSize;
//    }
    printf("\nDelta: %d\n", &delta);
    for(i = 0; i < bufferSize; i++){
        readBlocking(buffer->paginas[i].tuplas, file, tFactor - delta);
        printf("\nReading blocking file\n");
         int k = 0;
        printf("\n Reading file");
//        for(k = 0; k < tFactor; k++){
//            printf("\n %d", buffer->paginas[i].tuplas[k].id);
//        }
        printf("\n Finish register");
    }
}

void initBuffer2(struct Buffer2* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla2));

    int i = 0;
    //fseek(file, 0, posiInit * tFactor);

    int currentPosi = ftell(file);
    printf("\nCurrent Cursor Position in file: %d\n", &currentPosi);
    printf("\ntFactor: %d\n", tFactor);
    int delta = 0;
//    if(tFactor + currentPosi > fileSize){
//        delta = (tFactor + currentPosi) - fileSize;
//    }
    printf("\nDelta: %d\n", &delta);
    for(i = 0; i < bufferSize; i++){
        readBlocking2(buffer->paginas[i].tuplas, file, tFactor - delta);
        printf("\nReading blocking file\n");
         int k = 0;
        printf("\n Reading file");
//        for(k = 0; k < tFactor; k++){
//            printf("\n %d", buffer->paginas[i].tuplas[k].id);
//        }
        printf("\n Finish register");
    }
}

void join(struct Buffer1* buffer1, struct Buffer2* buffer2, int tCurrentBufferPage1, int tCurrentBufferPage2, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla1));
    int tFactor2 = blockingFactor(tPagina, sizeof(struct Tupla2));


    int i = 0;
    int j = 0;
    printf("\nJoin Tuplas");
    for(i = 0; i < tFactor / sizeof(struct Tupla1); i++){
        for(j = 0; j < tFactor2 / sizeof(struct Tupla2); j++){
            //printf("\n%d",buffer1->paginas[tCurrentBufferPage1].tuplas[i].id);
            if(buffer1->paginas[tCurrentBufferPage1].tuplas[i].id == buffer2->paginas[tCurrentBufferPage2].tuplas[j].id){
                printf("\n Match: %d %s %d %s ", buffer1->paginas[tCurrentBufferPage1].tuplas[i].id,buffer1->paginas[tCurrentBufferPage1].tuplas[i].city, buffer2->paginas[tCurrentBufferPage2].tuplas[j].id,buffer2->paginas[tCurrentBufferPage2].tuplas[j].street);
            }
        }
    }

}

void readBlocking(struct Tupla1* bloco, FILE* file, int sizeToRead){

//    fread(&bloco, sizeof(struct Tupla1), sizeToRead / sizeof(struct Tupla1), file);
    printf("\n Size To Read: %d", sizeToRead);


    int i = 0;

    for ( i = 0; i < sizeToRead/sizeof(struct Tupla1); i++){
        if(fscanf(file, "%d %s %s %d %s %s %d %d", &bloco[i].id, (&bloco[i])->firstName, (&bloco[i])->lastName, &bloco[i].age, (&bloco[i])->city, (&bloco[i])->state, &bloco[i].zipCode, &bloco[i].idCity) == EOF){
            break;
        }
        printf("\n%d %s %s %d %s %s %d %d", bloco[i].id, (&bloco[i])->firstName, (&bloco[i])->lastName, bloco[i].age, (&bloco[i])->city, (&bloco[i])->state, bloco[i].zipCode, bloco[i].idCity);
    }
}

void readBlocking2(struct Tupla2* bloco, FILE* file, int sizeToRead){

//    fread(&bloco, sizeof(struct Tupla1), sizeToRead / sizeof(struct Tupla1), file);
    printf("\n Size To Read: %d", sizeToRead);


    int i = 0;
    rewind(file);
    for ( i = 0; i < sizeToRead/sizeof(struct Tupla2); i++){
        if(fscanf(file, "%d %s %d", &bloco[i].id,&bloco[i].street, &bloco[i].zipCode) == EOF){
            break;
        }
        printf("\n%d %s %d", bloco[i].id, &bloco[i].street, &bloco[i].zipCode);
    }
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

void printRegister(struct Buffer1* buffer, int registerSize, int tPagina){
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

void printRegister2(struct Buffer2* buffer, int registerSize, int tPagina){
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

struct Tupla1* readTuplas(char* fileName){}

int fileSize(FILE* file){
    fseek (file, 0, SEEK_END);
    int t = ftell (file);
    fclose(file);
    return t;
}

int countRegisters(char* fileName){}

int amountPages(int bufferSize, int pagesSize){}

int pageSize(int blockingFactor){
    return ceil((sizeof(struct Tupla1) * blockingFactor));
}

int bufferPageFactor(int bufferSize, int pageSize){
    return ceil((bufferSize/pageSize));
}

int blockingFactor(int pageSize, int regSize){
    return floor(((pageSize *  KILOBYTE * KILOBYTE)/regSize));
}

void printFileContent(char* fileName, int pAmount){
    FILE* file = fopen(fileName, "r");
    struct Tupla1 * tuplas = malloc(sizeof(struct Tupla1) * pAmount);
    int i =0;
    int id = 0;
   // fread(&tuplas,  sizeof(struct Tupla1), pAmount, file);
    while(fscanf(file, "%d", &tuplas[i].id) != EOF){
         printf("\n %d", tuplas[i].id);
          i++;
      }

    printf("\n Reading file %s", fileName);
    for(i = 0; i < pAmount; i++){
        printf("\n %d", tuplas[i].id);
    }
    printf("\n Finish register");
    fclose(file);
}


void writeData(char* filename, int amountTupla){
    FILE* file = fopen(filename, "w+");
    struct Tupla1 * tuplas = malloc(sizeof(struct Tupla1) * amountTupla);

    int i = 0;
    for(i = 0; i < amountTupla; i++){

        fprintf(file,"%d\n",i);
    }
    printf("fasdoifjas");

    fclose(file);
}

