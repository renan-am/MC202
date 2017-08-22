#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

DISCO *inicializar_disco (int tamanho){
	//Inicializa disco
	DISCO *disco = NULL;
	disco = malloc(sizeof(DISCO));
	disco->tamanho_total = tamanho;
	disco->inicio = NULL;
	
	//cria uma sentinela, delimitando o início da lista
	BLOCO *sentinela = NULL;
	sentinela = malloc(sizeof(BLOCO));
	strcpy(sentinela->nome, "sentinela");
	sentinela->tamanho = 0;
	sentinela->prox = NULL;
	sentinela->ant = NULL;

	disco->inicio = sentinela;


	//cria um bloco representando o espaço livre
	BLOCO *inicial = NULL;
	inicial = malloc(sizeof(BLOCO));
	strcpy(inicial->nome, "livre");
	inicial->tamanho = tamanho;
	inicial->prox = NULL;
	inicial->ant = sentinela;

	sentinela->prox = inicial;

	return disco;
}


int adicionar_bloco (DISCO *disco, char nome[],int tam_adic){
	BLOCO *i = NULL;
	BLOCO *menor = NULL;

	for (i = disco->inicio->prox; i != NULL; i = i->prox){
		if (strcmp(i->nome, "livre") == 0  &&  i->tamanho >= tam_adic){
			if (menor == NULL)
				menor = i;
			else if (i->tamanho < menor->tamanho)
				menor = i;
		}
	}
	if (menor == NULL){
		return 1;
	}

	BLOCO *novo = NULL;
	novo = malloc(sizeof(BLOCO));

	strcpy(novo->nome, nome);
	novo->tamanho = tam_adic;
	novo->ant = menor->ant;
	menor->ant->prox = novo;

	if (menor->tamanho - tam_adic == 0){
		novo->prox = menor->prox;

			if (menor->prox != NULL)
				menor->prox->ant = novo;

		free (menor);
	} else {
		novo->prox = menor;
		menor->tamanho = menor->tamanho - tam_adic;
		menor->ant = novo;
	}

	return 0;
}


void concatena_livre (BLOCO **alvo){
	int prox_livre = 0, ant_livre = 0;


		if ((*alvo)->prox != NULL && strcmp ((*alvo)->prox->nome, "livre") == 0)
			prox_livre = 1;
		if (strcmp ((*alvo)->ant->nome, "livre") == 0)
			ant_livre = 1;
	

		if (prox_livre == 1 && ant_livre == 1){
			(*alvo)->ant->tamanho = ((*alvo)->ant->tamanho) + ((*alvo)->prox->tamanho) + ((*alvo)->tamanho);
			(*alvo)->ant->prox = (*alvo)->prox->prox;
			free (*alvo);
		} else if (prox_livre == 1 && ant_livre == 0){
			(*alvo)->prox->tamanho = ((*alvo)->prox->tamanho) + ((*alvo)->tamanho);
			(*alvo)->ant->prox = (*alvo)->prox;
			(*alvo)->prox->ant = (*alvo)->ant;
			free (*alvo);
		} else if (prox_livre == 0 && ant_livre == 1){
			(*alvo)->ant->tamanho = ((*alvo)->ant->tamanho) + ((*alvo)->tamanho);
			(*alvo)->ant->prox = (*alvo)->prox;

				if ((*alvo)->prox != NULL)
					(*alvo)->prox->ant = (*alvo)->ant;

			free (*alvo);
		} else {
			return;
		}
}

int remover_bloco (DISCO *disco, char nome[]){
	BLOCO *i = NULL;

	for (i = disco->inicio->prox; i != NULL && strcmp(i->nome, nome) != 0; i = i->prox){}


	if (i != NULL){
		strcpy(i->nome, "livre");
		concatena_livre(&i);
	}

	return 0;
}

int otimiza (DISCO *disco){
	BLOCO *i = NULL;
			

	for (i = disco->inicio->prox; i != NULL; i = i->prox){
		if (strcmp(i->ant->nome, "livre") == 0){
			i->ant->prox = i->prox;
			i->prox = i->ant;
			i->ant = i->ant->ant;
			i->ant->ant = i;
			imprimir_lista (disco);
			concatena_livre (&(i->prox));
			imprimir_lista (disco);
			
		}
	}
}

void imprimir_lista (DISCO *disco){
	BLOCO *i = NULL;

	for (i = disco->inicio; i != NULL; i=i->prox)
		printf ("-%s %d-", i->nome, i->tamanho);

	printf ("\n");
}

void liberar (DISCO **disco){
	BLOCO *i = (*disco)->inicio;
	BLOCO *j = i;

	while (i != NULL){
		i = i->prox;
		free (j);
		j = i;
	}

	free (*disco);

}