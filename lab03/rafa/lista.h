/* Rafael Sartori Martins dos Santos (RA: 186154) */
#ifndef LISTA_H
#define LISTA_H


typedef struct Item {
    /**
    * endereço do kb no disco
    */
    int chave;
    /**
    * tamanho em kb no disco
    */
    int tamanho_do_arquivo;
    char *nome_do_arquivo;
    struct Item* proximo;
} Item;

typedef struct {
    int tamanho;
    Item *inicio;
} Lista;

typedef struct {
    /**
    * Capacidade será medida em kb.
    *
    * Como a capacidade máxima é de 1023 Gb, podemos utilizar int se tudo for
    * colocado em unidades de kb.
    */
    int capacidade;
    /**
    * A lista deve permanecer ordenada em relação a chave (endereço do kb do
    * início do arquivo)
    */
    Lista *arquivos;
} Disco;


/**
* A função inicializa o ponteiro lista com uma lista vazia com as variáveis
* inicializadas.
*
* Retorna 0 caso não conseguir alocar memória dinâmica.
*/
int iniciar_lista(Lista **lista);

/**
* Esta função liberará toda a memória alocada para a lista. O ponteiro dado re-
* ceberá NULL.
*/
void liberar_lista(Lista **lista);

/**
* A função procura o menor bloco livre de memória que possa incluir o arquivo.
*
* Retorna -1 caso tenha ocorrido um erro
* Retorna  0 caso não seja possível incluir o arquivo.
* Retorna  1 caso o item foi adicionado.
*/
int inserir_no_disco(Disco *disco, char* nome_do_arquivo, int tamanho_do_arquivo);

/**
* A função remove o item de nome dado.
*
* Retorna 0 se o elemento não existir.
*/
int remove_do_disco(Disco *disco, char* nome_do_arquivo);

/**
* "Move os arquivos" para torná-los contíguos no disco.
*
* Não deve falhar... eu espero...
*/
void otimiza_disco(Disco *disco);

#endif /* LISTA_H */
