#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char *nome;
    int tam;
    struct no *prox;
}no;




void optimize(no **inic){

    no *p = *inic;
    no *ant = NULL;

    while (p != NULL && p->nome != 0){
        ant = p;
        p = p->prox;
    }
    if (p == NULL) return;

    no *ant_pp = p;
    no *pp = p->prox;
    while (pp != NULL && pp->nome == 0){
        ant_pp = pp;
        pp = pp->prox;
    }
    if (pp == NULL) return;

    //Joga conteudo para frente (se existir) trocando p e pp de lugar:

    no *aux = pp->prox;
    ant_pp->prox = p;
    pp->prox = p->prox;
    p->prox = aux;
     //Sendo ant == NULL, p sera o primeiro da lista, logo:
    if (ant != NULL) ant->prox = pp;
    else *inic = pp;

    //Junta todos os espacos vazios adjacentes:
    no *espaco = *inic;
    while (espaco != NULL){
        if (espaco->nome == 0){
            if(espaco->prox != NULL && espaco->prox->nome == 0){
                espaco->tam += espaco->prox->tam;
                no *proximo_espaco = espaco->prox;
                espaco->prox = proximo_espaco->prox;
                free(proximo_espaco);
            }
            else{
                espaco = espaco->prox;
            }
        }
        else{
            espaco = espaco->prox;
        }
    }

    optimize(inic); //Chama de novo ate que todos os espacos ocupados estejam juntos no comeco
    return;

}

no *criar_disco(int tam){

    no *p = malloc(sizeof(no));
    p->nome = 0;
    p->tam = tam;
    p->prox = NULL;
    return p;
}

no *criar_arquivo(char *nome, int tam){

    no *arq = malloc(sizeof(no));
    arq->nome = malloc(12*sizeof(char));
    strcpy(arq->nome, nome);
    arq->tam = tam;
    arq->prox = NULL;
    return arq;
}

int adicionar_arquivo(no **inic, no *add){

    no *ant = NULL;
    no *espaco = *inic;
    int i, soma = 0, this = -1, tam_this = 1024*1024*1024;

    for (i = 0; espaco != NULL; i++){
        espaco = espaco->prox;
    }
    int *pos = calloc (i ,sizeof(int));

    espaco = *inic;
    i = 0;
    while (espaco != NULL){
        if (espaco->tam >= add->tam && espaco->nome == 0){
            pos[i] = 1;
        }
        ant = espaco;
        espaco = espaco->prox;
        i++;
    }
    espaco = *inic;
    for (i = 0; espaco != NULL; i++){
        soma += pos[i];
        espaco = espaco->prox;
    }
    if (!soma){
        optimize(inic);
        i = 0;
        espaco = *inic;
        while (espaco != NULL){
            if (espaco->tam >= add->tam && espaco->nome == 0){
                pos[i] = 1;
            }
            ant = espaco;
            espaco = espaco->prox;
            i++;
        }
        espaco = *inic;
        for (i = 0; espaco != NULL; i++){
            soma += pos[i];
            espaco = espaco->prox;
        }
    }
    if (!soma){

        free(pos);
        return 0;
    }

    espaco = *inic;
    for (i = 0; espaco != NULL; i++){
        if (pos[i]){
            if (espaco->tam < tam_this){
                this = i;
                tam_this = espaco->tam;
            }
        }
        espaco = espaco->prox;
    }

    ant = NULL;
    espaco = *inic;
    for (i = 0; i < this; i++){
        ant = espaco;
        espaco = espaco->prox;
    }

    if (espaco->tam != add->tam){
        espaco->tam = espaco->tam - add->tam;
        add->prox = espaco;
        if (ant == NULL) (*inic) = add;
        else ant->prox = add;
    }
    else{
        espaco->nome = add->nome;
        free (add);
    }
    free(pos);

    return 1;
}

int remover_arquivo(no *inic, char *nome){

    no *espaco = inic;
    no *anterior = NULL;

    while (espaco != NULL){
        if (espaco->nome != 0 && !strcmp(espaco->nome, nome)){
            break;
        }
        anterior = espaco;
        espaco = espaco->prox;
    }
    if (espaco == NULL) return 0;
    free(espaco->nome);
    espaco->nome = 0;
    if(espaco->prox != NULL && espaco->prox->nome == 0){
        espaco->tam += espaco->prox->tam;
        no *p = espaco->prox;
        espaco->prox = p->prox;
        free(p);
    }
    if(anterior != NULL && anterior->nome == 0){
        anterior->tam += espaco->tam;
        anterior->prox = espaco->prox;
        free(espaco);
    }
    return 0;
}

void free_all(no *inicial){

    //Da free em todos os nos indo do primeiro ao ultimo
    no *pp = NULL;
    no *p = inicial;
    while(p != NULL){
        pp = p;
        p = p->prox;
        free(pp->nome);
        free(pp);
    }
}

int min(int a, int b){
    if (a>b) return b;
    else return a;
}

void printar_disco(no *inic, int tam){

    int celula[8];
    int ocupado[8];
    int total_celula = tam/8;
    no *p = inic;

    //Inicializa celula:
    int i;
    for (i = 0; i < 8; i++){
        celula[i] = 0;
        ocupado[i] = 0;
    }

    i = 0;
    while (p != NULL){
        while (p->tam > 0){
            int aux = celula[i];
            celula[i] += min(p->tam, (total_celula-aux));
            if (p->nome != 0){
                ocupado[i] += min(p->tam, (total_celula-aux));
            }
            p->tam -= min(p->tam, (total_celula-aux));

            if (celula[i] == total_celula){
                i++;
            }
        }
        p = p->prox;
    }

    for (i = 0; i < 8; i++){
        if(ocupado[i]*100/total_celula >= 75){
            printf("[#]");
        }
        else if (ocupado[i]*100/total_celula >= 25){
            printf("[-]");
        }
        else{
            printf("[ ]");
        }
    }
    printf("\n");
    return;
}
