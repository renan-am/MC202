#ifndef ARQ_INCL
#define ARQ_INCL

#include "lista.c"

typedef struct BLOCO{
	char nome[15];
	int tamanho;
	struct BLOCO *prox;
	struct BLOCO *ant;
} BLOCO;

typedef struct DISCO {
	int tamanho_total;

	BLOCO *inicio;
	BLOCO *prim_livre;

} DISCO;



#endif