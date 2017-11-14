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


DISCO *inicializar_disco (int tamanho);

int adicionar_bloco (DISCO *disco, char nome[],int tam_adic);

void concatena_livre (BLOCO *alvo);

int remover_bloco (DISCO *disco, char nome[]);

int otimiza (DISCO *disco);

void imprimir_lista (DISCO *disco);

void liberar (DISCO **disco);

void porcentagem_disco (DISCO *disco, double espacos[]);


#endif