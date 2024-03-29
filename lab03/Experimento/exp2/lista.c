#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

DISCO *inicializar_disco (int tamanho){
	//Inicializa disco
	DISCO *disco = NULL;
	disco = malloc(sizeof(DISCO));
	disco->tamanho_total = tamanho;
	disco->tamanho_vazio = tamanho;
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

	if (disco->tamanho_vazio < tam_adic){
		return 2;
	}

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

	if (menor->tamanho - tam_adic == 0){
		strcpy(menor->nome, nome);
	} else {
		BLOCO *novo = NULL;
		novo = malloc(sizeof(BLOCO));
		strcpy(novo->nome, nome);
		novo->tamanho = tam_adic;
		
		novo->ant = menor->ant;
		menor->ant->prox = novo;
		novo->prox = menor;
		menor->tamanho = menor->tamanho - tam_adic;
		menor->ant = novo;
	}

	disco->tamanho_vazio = disco->tamanho_vazio - tam_adic;

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
		disco->tamanho_vazio = disco->tamanho_vazio + i->tamanho;
		concatena_livre(i);
	}

	return 0;
}

int otimiza (DISCO *disco){
	BLOCO *i = NULL, *aux = NULL;
	int temp = 0;
			

	for (i = disco->inicio->prox; i != NULL; i = i->prox){
		if (strcmp(i->ant->nome, "livre") == 0){

			aux = i->ant;
			i->ant = i->ant->ant;
			i->ant->prox = i;
			free (aux);
		}

		if (i->prox == NULL && strcmp(i->nome, "livre") == 0){
			i->tamanho = disco->tamanho_vazio;
		}
		else if (i->prox == NULL){
			BLOCO *vazio = NULL;
			vazio = malloc (sizeof(BLOCO));
			strcpy(vazio->nome, "livre");
			vazio->tamanho = disco->tamanho_vazio;
			vazio->prox = i->prox;
			i->prox = vazio;
			vazio->ant = i;
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
	free (j);
	free (*disco);

}


void porcentagem_disco (DISCO *disco, double espacos[]){
	BLOCO *i = NULL;
	double aux = 0.0;
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
				espacos[j] = (double)tam_vazio/tam_parte;
				//printf ("tam_vazio = %d,     tam_ocupado= %d\n", tam_vazio, tam_ocupado);
				//printf ("espacos = %d e aux = %f\n", espacos[j], aux);
				//printf ("v_sobra = %d e o_sobra = %d\n",tam_vazio_sobra, tam_ocupado_sobra);

				j++;
				//printf ("antes - v_sobra = %d e o_sobra = %d\n%d     %d\n",tam_vazio_sobra, tam_ocupado_sobra, tam_vazio, tam_ocupado);
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
					tam_ocupado = tam_ocupado_sobra;
					tam_ocupado_sobra = 0;
				}
				//printf ("depois - v_sobra = %d e o_sobra = %d\n%d     %d\n",tam_vazio_sobra, tam_ocupado_sobra, tam_vazio, tam_ocupado);

			}while (tam_vazio + tam_ocupado >= tam_parte && j < 8);
		}
	}
	
}