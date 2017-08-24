#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main (){
	char com [3][10];
	srand(time(NULL));

	strcpy(com[0], "insere");
	strcpy(com[1], "remove");
	strcpy(com[2], "otimiza");

	char suf[3][10];

	strcpy(suf[0], "Kb");
	strcpy(suf[1], "Mb");
	strcpy(suf[2], "Gb");

	int qtd = 0;
	scanf ("%d", &qtd);

	/*char **hist = NULL;

	hist = calloc (qtd, sizeof(char));

	for (int i; i < qtd; i++)
		hist[i] = calloc (10, sizeof(char));
*/

	int hist[qtd];
	int count = 0;
	for (int i = 0; i < qtd; i++)
		hist[i] = 0;

	int tamanhoDisco = 0;

	int indice = 0;
	int tam = 0; 
	int nome = 0;


	char acao[10];
	char arquivo[50];
	char tamanho[10];
	char sufixo[10];

	tamanhoDisco = (rand()%128 + 1)*8;
	indice = rand()%3;
	strcpy(sufixo, suf[indice]);

	printf("%d\n%d%s\n", qtd,tamanhoDisco,sufixo);

	for (int j = 0; j < qtd; j++){
		indice = rand()%3;
		strcpy(acao, com[indice]);

		if (strcmp(acao, "insere") == 0){
			while(1){
				nome = rand();
				sprintf(arquivo, "%d", nome);
				int i;
				for (i = 0; i <qtd; i++){
					if (hist[i] == nome){
						strcpy(arquivo, " ");
						break;
					}
				}
				if (i == qtd)
					break;
			}
			hist[count] = nome;
			count++;
			tam = rand()%1024 + 1;
			indice = rand()%3;
			strcpy(sufixo, suf[indice]);
			printf ("%s %s %d%s\n",acao, arquivo, tam, sufixo);
			strcpy(arquivo, "");
		} else if (strcmp(acao, "remove") == 0){
			indice = rand()%qtd;
			nome = hist[indice];
			sprintf(arquivo, "%d", nome);
			printf ("%s %s \n", acao, arquivo);
			strcpy(arquivo, " ");
			for (int i = 0; i <qtd; i++)
					if (hist[i] == nome)
						hist[i] = 0;
		} else {
			printf ("%s \n", acao);
		}
	}

	printf ("0 \n");


}