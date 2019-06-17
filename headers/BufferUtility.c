//#include "BufferUtility.h"
//#define KILOBYTE 1024
//
//void createBuffer(struct Buffer* buffer, int bufferSize, int tPagina){
//    int i = 0;
//    buffer->paginas = (struct Pagina*)malloc(bufferSize * sizeof(struct Pagina));
//
//    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
//
//    printf("\n %d \n", tFactor);
//
//    for(i = 0; i < bufferSize; i++){
//         buffer->paginas[i].tuplas = (struct Tupla*)malloc(tFactor);
//    }
//
//};
//
//void initBuffer(struct Buffer* buffer, FILE* file, int posiInit, int fileSize, int bufferSize, int tPagina){
//    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
//
//    int i = 0;
//    fseek(file, 0, posiInit);
//
//    int currentPosi = ftell(file);
//
//    int delta = 0;
//    if(tFactor + currentPosi > fileSize){
//        delta = (tFactor + currentPosi) - fileSize;
//    }
//    for(i = 0; i < bufferSize; i++){
//        buffer->paginas[i].tuplasize = tFactor - delta;
//        readBlocking(buffer->paginas[i].tuplas, file, tFactor - delta, bufferSize);
//    }
//}
//
//void join(struct Buffer* buffer1, struct Buffer* buffer2, int buffer1Size, int buffer2Size, int tPagina){
//    int tFactor = blockingFactor(tPagina, sizeof(struct Tupla));
//
//    int i = 0;
//    int j = 0;
//    int k = 0;
//    int w = 0;
//
//    for(i = 0; i < buffer1Size; i++){
//        for(j = 0; j < buffer2Size; j++){
//            for(k = 0; k < buffer1->paginas[i].tuplasize; k++){
//                for(w = 0; w < buffer1->paginas[j].tuplasize; w++){
//                    if(buffer1->paginas[i].tuplas[k].id == buffer2->paginas[j].tuplas[w].id){
//                        printf("%d %d", buffer1->paginas[i].tuplas[k].id, buffer1->paginas[j].tuplas[w].id);
//                    }
//                }
//            }
//        }
//    }
//}
//
//void readBlocking(struct Tupla* bloco, FILE* file, int sizeToRead, int bufferSize){
//
//    fread(&bloco, sizeof(struct Tupla), sizeToRead, file);
//
//}
//
//void clearBuffer (struct Buffer* buffer, int pBufferSize){
//    int i = 0;
//    for(i = 0; i < pBufferSize; i++){
//       free(buffer->paginas[i].tuplas);
//    }
//    free(buffer->paginas);
//    free(buffer);
//}
//
//void printRegister(struct Buffer* buffer, int registerSize, int tPagina){
//    int i = 0;
//    int j = 0;
//    int id = 0;
//    printf("Registros pagina %d\n", tPagina);
//    for(j = 0; j < registerSize; j++){
//        printf( "%d \n", buffer->paginas[tPagina].tuplas[j].id);
//    //           buffer->paginas[tPagina].tuplas[j].cpf,
//     //          buffer->paginas[tPagina].tuplas[j].nome);
//    }
//
//}
//
//struct Tupla* readTuplas(char* fileName){}
//
//int fileSize(FILE* file){
//    fseek (file, 0, SEEK_END);
//    int t = ftell (file);
//    fclose(file);
//    return t;
//}
//
//int countRegisters(char* fileName){}
//
//int amountPages(int bufferSize, int pagesSize){}
//
//int bufferSize(struct Buffer* buffer){}
//
//int pageSize(int blockingFactor){
//    return ceil((sizeof(struct Tupla) * blockingFactor));
//}
//
//int bufferPageFactor(int bufferSize, int pageSize){
//    return ceil((bufferSize/pageSize));
//}
//
//int blockingFactor(int pageSize, int regSize){
//    return ceil(((pageSize * KILOBYTE * KILOBYTE)/regSize));
//}
//
//
//void writeData(char* filename, int amountTupla){
//    FILE* file = fopen(filename, "w+");
//    struct Tupla * tuplas = malloc(sizeof(struct Tupla) * amountTupla);
//
//    int i = 0;
//   // for(i = 0; i < amountTupla; i++){
//        struct Tupla tupla;
//        tupla.id = 1;
//        fwrite(&tupla,  sizeof(struct Tupla), 1, file);
//
//    //}
//
//    fclose(file);
//}
