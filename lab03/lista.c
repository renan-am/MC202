#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

DISCO *inicializar_disco (int tamanho){
	
	DISCO *disco = NULL;

	disco = malloc(sizeof(DISCO));
	disco->tamanho_total = tamanho;
	disco->inicio = NULL;

	//cria um bloco representando o espaço livre
	BLOCO *inicial = NULL;

	inicial = malloc(sizeof(BLOCO));
	strcpy(inicial->nome, "livre");
	inicial->tamanho = tamanho;
	inicial->prox = NULL;
	inicial->ant = NULL;


	disco->inicio = inicial;

	return disco;
}