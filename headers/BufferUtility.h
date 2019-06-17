//struct Tupla{
//    int id;
//};
//
//struct Pagina{
//    struct Tupla* tuplas;
//    int tuplasize;
//};
//
//struct Buffer{
//    struct Pagina* paginas;
//};
//#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//
///// Inicia o buffer
//void createBuffer(struct Buffer* buffer, int bufferSize, int tPagina);
//
//void initBuffer(struct Buffer* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina);
//
//void printRegister(struct Buffer* buffer, int registerSize, int tPagina);
//
///// Le todas as tuplas dentro do root do projeto
//struct Tupla* readTuplas(char* fileName);
//
//int amountPages(int bufferSize, int pagesSize);
//
///// conta o total de registro dentro do arquivo
//int countRegisters(char* fileName);
//
///// Cria as paginas
//struct Pagina* createPages(struct Tupla* tuplas, int regAmount);
//
//void clearBuffer (struct Buffer* buffer, int pBufferSize);
//
//void readBlocking(struct Tupla* bloco, FILE* file, int sizeToRead, int bufferSize);
//
///// Calcula o tamnho do registro
//int bufferSize(struct Buffer* buffer);
//
///// Calcula o tamanho da pagina
//int pageSize(int blockingFactor);
//
///// Calcula o fator de pagina do buffer
//int bufferPageFactor(int bufferSize, int pageSize);
//
///// Calcula o fator de blocagem
//int blockingFactor(int pageSize, int regSize);
//
//void writeData(char* filename, int amountTupla);
