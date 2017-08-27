/* Rafael Sartori Martins dos Santos (RA: 186154) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


int iniciar_lista(Lista **lista) {
    Lista *auxiliar = malloc(sizeof(Lista));
    if(auxiliar == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nova lista.\n");
        return 0;
    }

    // Inicializando lista
    auxiliar->inicio = NULL;
    auxiliar->tamanho = 0;
    // Passamos para a lista
    *lista = auxiliar;
    return 1;
}

void liberar_lista(Lista **lista) {
    while((*lista)->inicio != NULL) {
        // Guardamos o item a ser removido
        Item *auxiliar = (*lista)->inicio;

        // Removemos o elemento da lista (de modo a parar a iteração quando a
        // lista acabar)
        (*lista)->inicio = (*lista)->inicio->proximo;
        (*lista)->tamanho--;

        // Liberamos o arquivo auxiliar
        free(auxiliar->nome_do_arquivo);
        free(auxiliar);
    }

    // Liberamos a lista por fim
    free(*lista);
    *lista = NULL;
}

int inserir_no_disco(Disco *disco, char* nome_do_arquivo, int tamanho_do_arquivo) {
    // Caso o arquivo seja maior que a capacidade do disco, paramos
    if(tamanho_do_arquivo > disco->capacidade)
        return 0;

    /**
    * Endereço do início do arquivo
    */
    // Colocamos endereço em 0 pois se o tamanho do arquivo for 0, será isso
    // se não, verificaremos o menor bloco (retornando ou substituindo o valor).
    int endereco = 0;

    // Se o disco está vazio e há espaço, incluímos no começo
    if(disco->arquivos->tamanho != 0) {
        /*
        * Devemos, agora, procurar o início do menor bloco de memória livre que
        * tenha espaço para o arquivo
        */

        // Consideramos o endereço do menor tamanho indefinido
        int endereco_menor = -1;
        // O menor_tamanho inicial é a capacidade do disco, para substituírmos
        int menor_tamanho = disco->capacidade;

        Item *arquivo = disco->arquivos->inicio;
        for(; arquivo != NULL; arquivo = arquivo->proximo) {
            /*
            * Calcularemos o espaço livre entre os arquivos
            *
            * Para isso, pegamos o endereço do arquivo + seu tamanho e conferi-
            * mos o tamanho até o endereço de início do próximo arquivo ou até
            * o final do disco, se inexistente.
            */

            int tamanho_atual = 0;
            int endereco_fim = (arquivo->chave + arquivo->tamanho_do_arquivo);
            if(arquivo->proximo != NULL) {
                /*
                * Caso o arquivo existir, pegamos o tamanho do final do arquivo
                * atual até o próximo arquivo
                */
                tamanho_atual = arquivo->proximo->chave - endereco_fim;
            } else {
                // Caso não existir, conferimos com o final do disco
                tamanho_atual = disco->capacidade - endereco_fim;
            }

            // Atualizamos as informações caso o espaço for suficiente e for
            // o menor bloco
            if(tamanho_atual >= tamanho_do_arquivo &&
                    (
                        // Caso encontramos um bloco MENOR
                        menor_tamanho > tamanho_atual ||
                        // OU encontramos um bloco igual mais próximo do início
                        (menor_tamanho == tamanho_atual &&
                            endereco_menor > endereco_fim)
                    )
                ) {
                menor_tamanho = tamanho_atual;
                endereco_menor = endereco_fim;
            }
        }

        // Caso não encontramos um bloco suficiente, retornamos falha
        if(endereco_menor < 0)
            return 0;
        else
            endereco = endereco_menor;
    }

    /*
    * Agora que temos o endereço do menor bloco capaz de armazenar o arquivo,
    * criamos o registro do arquivo
    */
    {
        Item *item_criado = malloc(sizeof(Item));
        if(item_criado == NULL) {
            fprintf(stderr, "Erro ao alocar memória para novo item.\n");
            return -1;
        }

        // NÃO PODEMOS ADICIONAR NO TOPO! DEVEMOS MANTER A ORDEM DA LISTA!
        {
            // Adicionamos o elemento cujo endereço já é maior do que o do item
            // a ser criado como próximo
            Item *auxiliar = disco->arquivos->inicio;

            if(auxiliar == NULL) {
                // Caso não haja lista, colocamos o novo item
                disco->arquivos->inicio = item_criado;
                disco->arquivos->tamanho++;
                item_criado->proximo = NULL;
            } else {
                // Caso haja lista...

                if(disco->arquivos->inicio->chave > endereco) {
                    // Precisamos conferir se a nova chave vira a cabeça
                    item_criado->proximo = disco->arquivos->inicio;
                    disco->arquivos->inicio = item_criado;
                    disco->arquivos->tamanho++;
               } else {
                    // Caso não virará a nova cabeça, colocamos no meio da lista
                    for(; auxiliar != NULL; auxiliar = auxiliar->proximo) {
                        // Encontramos o final da lista ou o elemento que é
                        // maior do que o endereço atual
                        if(auxiliar->proximo == NULL ||
                                auxiliar->proximo->chave > endereco)
                            break;
                    }
                    item_criado->proximo = auxiliar->proximo;
                    // Adicionamos a cabeça à lista
                    auxiliar->proximo = item_criado;
                    disco->arquivos->tamanho++;
                }
            }
        }

        // Colocamos no primeiro kb do disco
        item_criado->chave = endereco;

        // Adicionamos o nome ao arquivo
        item_criado->nome_do_arquivo = malloc(
            (strlen(nome_do_arquivo) + 1) * sizeof(char)
        );
        /*
        * Apesar de conferirmos isso, não vou tratar o erro na lista, pois é
        * um erro trabalhoso de arrumar pelo modelo que fiz a lista (deixando a
        * lista criar e adicionar o item e não apenas adicionar)
        */
        if(item_criado->nome_do_arquivo == NULL)
            return -1;
        // Preenchemos o nome_do_arquivo
        strcpy(item_criado->nome_do_arquivo, nome_do_arquivo);

        // Colocamos o tamanho do arquivo
        item_criado->tamanho_do_arquivo = tamanho_do_arquivo;
        return 1;
    }
}

int remove_do_disco(Disco *disco, char* nome_do_arquivo) {
    if(disco->arquivos->tamanho == 0)
        return 0;

    Item *arquivo = disco->arquivos->inicio;
    if(strcmp(nome_do_arquivo, disco->arquivos->inicio->nome_do_arquivo) == 0) {
        // Removemos da lista
        disco->arquivos->inicio = disco->arquivos->inicio->proximo;
        disco->arquivos->tamanho--;
        // Liberamos o item removido
        free(arquivo->nome_do_arquivo);
        free(arquivo);
        return 1;
    }

    // Já conferimos o primeiro arquivo, conferimos o resto
    for(; arquivo->proximo != NULL; arquivo = arquivo->proximo) {
        // Conferimos o nome do próximo arquivo, já que sabemos que ele existe
        if(strcmp(nome_do_arquivo, arquivo->proximo->nome_do_arquivo) == 0) {
            // Ao invés de removermos da lista pelo lista.h, fazemos manualmente
            Item *auxiliar = arquivo->proximo;
            // Removemos da lista
            arquivo->proximo = arquivo->proximo->proximo;
            disco->arquivos->tamanho--;
            // Liberamos o item removido
            free(auxiliar->nome_do_arquivo);
            free(auxiliar);
            return 1;
        }
    }

    // Retornamos se não encontramos o item
    return 0;
}

void otimiza_disco(Disco *disco) {
    Item *arquivo = disco->arquivos->inicio;

    /** É o endereço do próximo arquivo na lista */
    // Começamos com o primeiro item
    int endereco_proximo = 0;

    for(; arquivo != NULL; arquivo = arquivo->proximo) {
        arquivo->chave = endereco_proximo;
        endereco_proximo = arquivo->chave + arquivo->tamanho_do_arquivo;
    }
}
