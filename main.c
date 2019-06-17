#include <stdio.h>
#include <stdlib.h>
#define KILOBYTE 1024

struct Tupla{
    int id;
};

struct Pagina{
    struct Tupla* tuplas;
};

struct Buffer{
    struct Pagina* paginas;
};

/// Inicia o buffer
void createBuffer(struct Buffer* buffer, int bufferSize, int tPagina);

void initBuffer(struct Buffer* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina);

void printRegister(struct Buffer* buffer, int registerSize, int tPagina);

/// Le todas as tuplas dentro do root do projeto
struct Tupla* readTuplas(char* fileName);

int amountPages(int bufferSize, int pagesSize);

/// conta o total de registro dentro do arquivo
int countRegisters(char* fileName);

void printFileContent(char* fileName, int pAmount);

/// Cria as paginas
struct Pagina* createPages(struct Tupla* tuplas, int regAmount);

void clearBuffer (struct Buffer* buffer, int pBufferSize);

void readBlocking(struct Tupla* bloco, FILE* file, int sizeToRead, int bufferSize);

/// Calcula o tamnho do registro
int bufferSize(struct Buffer* buffer);

/// Calcula o tamanho da pagina
int pageSize(int blockingFactor);

/// Calcula o fator de pagina do buffer
int bufferPageFactor(int bufferSize, int pageSize);

/// Calcula o fator de blocagem
int blockingFactor(int pageSize, int regSize);

void writeData(char* filename, int amountTupla);

int main()
{
    int tamBuffer = 24;

    int tPagina = 2;

    char* fileName1 = "file1.txt";
    printf("write file 1");
    writeData(fileName1, 50);
    printFileContent(fileName1, 15);
    int file1Size = fileSize(fopen(fileName1, "r"));
    printf("\n File 1 Size: %d bytes", &file1Size);
    printf("\n\nWrited file 1");



    char* fileName2 = "file2.txt";
    printf("\nWrite file 2");
    writeData(fileName2, 50);
    int file2Size = fileSize(fopen(fileName2, "r"));
    printFileContent(fileName2, 7);

    printf("\n File 2 Size: %d bytes", &file2Size);
    printf("\n\nWrited file 2");

    FILE* file1 = fopen(fileName1, "r");

    FILE* file2 = fopen(fileName2, "r");


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


    struct Buffer* interno =  (struct Buffer*)malloc(sizeof(struct Buffer));

    printf("\nCreating buffer interno\n");

    createBuffer(interno, sizeInterno, tPagina);

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
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
    for(i = 0; i < externo; i++){
        initBuffer(externo, file1, i, file1Size, sizeExterno, tPagina);
        for(j = 0; j < interno; j++){
            initBuffer(interno, file2, j, file2Size, sizeInterno, tPagina);
            join(externo, interno, sizeExterno, sizeInterno, tPagina);
        }
        clearBuffer(externo, sizeExterno);
        clearBuffer(interno, sizeInterno);
    }


    return 0;
}


void createBuffer(struct Buffer* buffer, int bufferSize, int tPagina){
    int i = 0;
    buffer->paginas = (struct Pagina*)malloc(bufferSize * sizeof(struct Pagina));

    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));

    printf("\n %d \n", tFactor);

//    for(i = 0; i < bufferSize; i++){
//         buffer->paginas[i].tuplas = (struct Tupla*)malloc(tFactor);
//    }

}

void initBuffer(struct Buffer* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));

    int i = 0;
    fseek(file, 0, posiInit * tFactor);

    int currentPosi = ftell(file);
    printf("\nCurrent Cursor Position in file: %d\n", &currentPosi);
    printf("\ntFactor: %d\n", &tFactor);
    int delta = 0;
//    if(tFactor + currentPosi > fileSize){
//        delta = (tFactor + currentPosi) - fileSize;
//    }
    printf("\nDelta: %d\n", &delta);
    for(i = 0; i < bufferSize; i++){
        readBlocking(buffer->paginas[i].tuplas, file, tFactor - delta, bufferSize);
        printf("\nReading blocking file\n");
         int k = 0;
        printf("\n Reading file");
        for(k = 0; k < tFactor; k++){
            printf("\n %d", buffer->paginas[i].tuplas[k].id);
        }
        printf("\n Finish register");
    }
}

void join(struct Buffer* buffer1, struct Buffer* buffer2, int tCurrentBufferPage1, int tCurrentBufferPage2, int tPagina){
    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));


    int i = 0;
    int j = 0;

    for(i = 0; i < tFactor / sizeof(struct Tupla); i++){
        for(j = 0; j < tFactor / sizeof(struct Tupla); j++){
            if(buffer1->paginas[tCurrentBufferPage1].tuplas[i].id == buffer2->paginas[tCurrentBufferPage2].tuplas[j].id){
                printf("%d %d", buffer1->paginas[tCurrentBufferPage1].tuplas[i].id, buffer1->paginas[tCurrentBufferPage2].tuplas[j].id);
            }
        }
    }

}

void readBlocking(struct Tupla* bloco, FILE* file, int sizeToRead, int bufferSize){

    fread(&bloco, sizeof(struct Tupla), sizeToRead / sizeof(struct Tupla), file);

}

void clearBuffer (struct Buffer* buffer, int pBufferSize){
    int i = 0;
    for(i = 0; i < pBufferSize; i++){
       free(buffer->paginas[i].tuplas);
    }
    free(buffer->paginas);
    free(buffer);
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

int fileSize(FILE* file){
    fseek (file, 0, SEEK_END);
    int t = ftell (file);
    fclose(file);
    return t;
}

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

void printFileContent(char* fileName, int pAmount){
    FILE* file = fopen(fileName, "r");
    struct Tupla * tuplas = malloc(sizeof(struct Tupla) * pAmount);

    fread(&tuplas,  sizeof(struct Tupla), (int)(pAmount / sizeof(struct Tupla)), file);

    int i = 0;
    printf("\n Reading file %s", fileName);
    for(i = 0; i < pAmount; i++){
        printf("\n %d", tuplas[i].id);
    }
    printf("\n Finish register");
    fclose(file);
}


void writeData(char* filename, int amountTupla){
    FILE* file = fopen(filename, "w+");
    struct Tupla * tuplas = malloc(sizeof(struct Tupla) * amountTupla);

    int i = 0;
    for(i = 0; i < amountTupla; i++){
        tuplas[i].id = i;
    }
    fwrite(&tuplas,  sizeof(struct Tupla), amountTupla, file);
    fclose(file);
}

