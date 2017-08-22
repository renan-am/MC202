#ifndef ARQ_INCL
#define ARQ_INCL


typedef struct BLOCO{
	char nome[15];
	int tamanho;
	struct BLOCO *prox;
	struct BLOCO *ant;
} BLOCO;

typedef struct DISCO {
	int tamanho_total;

	BLOCO *inicio;

} DISCO;

void imprimir_lista (DISCO *disco);


#endif