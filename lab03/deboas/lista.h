
typedef struct no{
    char *nome;
    int tam;
    struct no *prox;
}no;

no *criar_disco(int tam);
no *criar_arquivo(char *nome, int tam);
int adicionar_arquivo(no **inic, no *add);
int remover_arquivo(no *inic, char *nome);
void optimize(no **inic);
void free_all(no *inicial);
void printar_disco(no *inic, int tam);
