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


void concatena_livre (BLOCO *alvo){
	int prox_livre = 0, ant_livre = 0;


		if (alvo->prox != NULL && strcmp (alvo->prox->nome, "livre") == 0)
			prox_livre = 1;
		if (strcmp (alvo->ant->nome, "livre") == 0)
			ant_livre = 1;
		

		if (prox_livre == 1 && ant_livre == 1){
			alvo->ant->tamanho = (alvo->ant->tamanho) + (alvo->prox->tamanho) + (alvo->tamanho);
			alvo->ant->prox = alvo->prox->prox;

				if (alvo->prox->prox != NULL){
					(alvo->prox->prox->ant = alvo->ant);
				}

			free (alvo->prox);
			free (alvo);
		} else if (prox_livre == 1 && ant_livre == 0){
			alvo->prox->tamanho = (alvo->prox->tamanho) + (alvo->tamanho);
			alvo->prox->ant = alvo->ant;	
			alvo->ant->prox = alvo->prox;

			free (alvo);
		} else if (prox_livre == 0 && ant_livre == 1){
			alvo->ant->tamanho = alvo->ant->tamanho + alvo->tamanho;
			alvo->ant->prox = alvo->prox;

				if (alvo->prox != NULL)
					alvo->prox->ant = alvo->ant;

			free (alvo);
		} else {
			return;
		}
}

int remover_bloco (DISCO *disco, char nome[]){
	BLOCO *i = NULL;

	for (i = disco->inicio->prox; i != NULL && strcmp(i->nome, nome) != 0; i = i->prox){}


	if (i != NULL){
		strcpy(i->nome, "livre");
		concatena_livre(i);
	}

	return 0;
}

int otimiza (DISCO *disco){
	BLOCO *i = NULL;
			

	for (i = disco->inicio->prox; i != NULL; i = i->prox){
		if (strcmp(i->ant->nome, "livre") == 0){

			if (i->prox != NULL){
				i->prox->ant = i->ant;
			}

			i->ant->prox = i->prox;
			i->prox = i->ant;
			i->ant = i->prox->ant;
			i->ant->prox = i;
			i->prox->ant = i;


			concatena_livre(i->prox);


		}
	}
	return 0;
}

void imprimir_lista (DISCO *disco){
	BLOCO *i = NULL;
	BLOCO *j = NULL;
	for (i = disco->inicio; i != NULL; i=i->prox){
		printf ("-%s %d-", i->nome, i->tamanho);
		j = i;
	}

	printf ("\n");

	for (i = j; i != NULL; i=i->ant)
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


void porcentagem_disco (DISCO *disco, int espacos[]){
	BLOCO *i = NULL;
	float aux = 0.0;
	int j = 0;
	int tam_vazio_sobra = 0, tam_ocupado_sobra = 0;
	int tam_vazio = 0, tam_ocupado = 0, tam_parte = 0;

	tam_parte = (disco->tamanho_total)/8;

	//imprimir_lista(disco);

	for (i = disco->inicio->prox; i != NULL; i=i->prox){
		if (strcmp(i->nome, "livre") == 0){
			tam_vazio += i->tamanho;
				if (tam_vazio + tam_ocupado > tam_parte){
					tam_vazio_sobra = tam_vazio + tam_ocupado - tam_parte;
					tam_vazio -= tam_vazio_sobra;
				}
		} else {
			tam_ocupado += i->tamanho;
				if (tam_vazio + tam_ocupado > tam_parte){
					tam_ocupado_sobra = tam_vazio + tam_ocupado - tam_parte;
					tam_ocupado -= tam_ocupado_sobra;
				}
		}
				//printf ("ENTROU = > v_sobra = %d e o_sobra = %d\n",tam_vazio_sobra, tam_ocupado_sobra);
		if (tam_vazio + tam_ocupado == tam_parte){
			do{
				aux = (float)tam_vazio/tam_parte;
				espacos[j] = 100*aux;
				//printf ("tam_vazio = %d,     tam_ocupado= %d\n", tam_vazio, tam_ocupado);
				//printf ("espacos = %d e aux = %f\n", espacos[j], aux);
				//printf ("v_sobra = %d e o_sobra = %d\n",tam_vazio_sobra, tam_ocupado_sobra);

				j++;

				if (tam_vazio_sobra >= tam_parte){
					tam_vazio = tam_parte;
					tam_vazio_sobra -= tam_parte;
				} else {
					tam_vazio = tam_vazio_sobra;
					tam_vazio_sobra = 0;
				}

				if (tam_ocupado_sobra >= tam_parte){
					tam_ocupado = tam_parte;
					tam_ocupado_sobra -= tam_parte;
				} else {
					tam_ocupado = tam_vazio_sobra;
					tam_ocupado_sobra = 0;
				}
				//printf ("v_sobra = %d e o_sobra = %d\n%d     %d\n",tam_vazio_sobra, tam_ocupado_sobra, tam_vazio, tam_ocupado);

			}while (tam_vazio + tam_ocupado >= tam_parte && j < 8);
		}
	}
	
}