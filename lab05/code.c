#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char indice;
	struct node *esquerda;
	struct node *direita;
} node;

void reconstroi (node **novo, char *preOrdem, char *emOrdem){
	int i = 0, j = 0, tam = 0;
	tam = strlen(preOrdem);

	node *temp = NULL;
	temp = malloc (sizeof(node));
	temp->indice = preOrdem[0];
	temp->esquerda = NULL;
	temp->direita = NULL;

	*novo = temp;

	if (tam == 1){
		return;
	} else {
		for (i = 0; preOrdem[i] != emOrdem[i]; i++){
		}

	}
}



int main (){
	node *arvore;

	arvore = malloc(sizeof(node));
	arvore->indice = 0;
	arvore->esquerda = NULL;
	arvore->direita = NULL;



}