#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//REMOVER
#include "lista.c"


int converter_tamanho(char tamanho[]){
	int qtd = strlen(tamanho);
	int i, j, fator;
	int tam = 0;
	char sufixo[3];

	for (i = qtd-2, j = 0; i <= qtd; i++, j++){
		sufixo[j] = tamanho[i];
	}
	for (i = qtd-3, fator = 1; i >=0; i--, fator = fator*10){
		tam += fator*(tamanho[i] - '0');
	}

	if (strcmp(sufixo, "Kb") == 0){
		return tam;
	} else if (strcmp(sufixo, "Mb") == 0) {
		return (tam*1024);
	} else if (strcmp(sufixo, "Gb") == 0) {
		return (tam*1024*1024);
	}
	return 0;
}


int main (){
	DISCO *disco;
	int tam_disco, testes, i, tam_bloco, flag;
	
	char nome[15], acao[10], tamanho[10], tamanho_disco[10];

	while (1){
		int espacos[8] = {100,100,100,100,100,100,100,100};
		flag = 0;
		scanf ("%d", &testes);
		if (!testes){
			break;
		}


		scanf ("%s", tamanho_disco);
		tam_disco = converter_tamanho(tamanho_disco);
		disco = inicializar_disco(tam_disco);

		for (i = 0; i < testes; i++){
			scanf ("%s", acao);

			if (strcmp(acao, "insere") == 0){
				scanf ("%s", nome);
				scanf ("%s", tamanho);
				tam_bloco = converter_tamanho(tamanho);

				if ((adicionar_bloco(disco, nome, tam_bloco)) != 0){
					otimiza(disco);
					if ((adicionar_bloco(disco, nome, tam_bloco)) != 0 && flag != 1){
						printf ("ERRO: disco cheio\n");
						flag = 1;
						continue;
					}
				}
			} 
			else if (strcmp(acao, "remove") == 0){
				scanf ("%s", nome);
				remover_bloco(disco, nome);
			} 
			else if (strcmp(acao, "otimiza") == 0){
				otimiza(disco);
			}
		}

		if (flag){
			liberar(&disco);
			continue;
		}

		porcentagem_disco(disco, espacos);

		for (i = 0; i < 8; i++){
			if (espacos[i] > 75){
				printf("[ ]");
			} else if (espacos[i] > 25){
				printf ("[-]");
			} else {
				printf ("[#]");
			}
		}
		printf ("\n");

		liberar(&disco);
	}

	return 0;
	
}

