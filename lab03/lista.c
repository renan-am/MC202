#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int inicializar_disco (DISCO **disco, int tamanho){
	
	//incializa disco
	*disco = malloc(sizeof(DISCO));

	if (*disco == NULL)

	(*disco)->tamanho_total = tamanho;
	(*disco)->inicio = NULL;
	(*disco)->prim_livre = NULL;

	//cria um bloco representando o espaço livre
	BLOCO *inicial = NULL;
	inicial = malloc(sizeof(BLOCO));
	strcpy(inicial->nome, "livre");
	inicial->tamanho = tamanho;


	(*disco)->inicio = inicial;
	return 0;
}