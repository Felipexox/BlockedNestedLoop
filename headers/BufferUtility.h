struct Tupla{
    int id;
    char nome[40];
    char cpf[11];
};

struct Pagina{
    struct Tupla tuplas[3];
};

struct Buffer{
    struct Pagina* paginas;
};

/// Inicia o buffer
void createBuffer();

/// Le todas as tuplas dentro do root do projeto
struct Tupla* readTuplas(char* fileName);

/// conta o total de registro dentro do arquivo
int countRegisters(char* fileName);

/// Cria as paginas
struct Pagina* createPages(struct Tupla* tuplas, int regAmount);

/// Calcula o tamnho do registro
int bufferSize(struct Buffer* buffer);

/// Calcula o tamanho da pagina
int pageSize(struct Pagina* page);

/// Calcula o fator de pagina do buffer
int pageFactor(int bufferSize, int pageSize);

/// Calcula o fator de blocagem
int blockingFactor(int pageSize, int regSize);
