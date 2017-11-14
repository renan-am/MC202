#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


int main(){
    int n, tam_disco, tam, rem, marcador = 1, parada = 1;
    char unidade, op[8], nome[11];
    no *inicial;
    // int pito = 0;

    while(1){
        scanf ("%d", &n);
        if (!n) break;
        scanf ("%d",  &tam_disco);
        unidade = getchar();

        if (unidade == 'M') tam_disco *= 1024;
        if (unidade == 'G') tam_disco *= 1024*1024;

        inicial = criar_disco (tam_disco);

        unidade = getchar();
        int i;
        for (i = 0; i < n; i++){
            scanf("%s", op);

            if (!strcmp(op, "insere")){
                scanf ("%s %d", nome, &tam);
                unidade = getchar();
                if (parada){
                    if (unidade == 'M') tam *= 1024;
                    if (unidade == 'G') tam *= 1024*1024;
                    no *add = criar_arquivo(nome, tam);

                    marcador = adicionar_arquivo(&inicial, add);
                    // free(add);
                }
            }
            else if (!strcmp(op,"remove")){
                scanf("%s", nome);
                if (parada)
                rem = remover_arquivo(inicial, nome);
            }
            else{
                optimize(&inicial);
            }

            unidade = getchar();
            if(!marcador) parada = 0;
        }

        // pito++;
        // printf("%d - ", pito);
        if(marcador) printar_disco(inicial, tam_disco);
        else printf("ERRO: disco cheio\n");

        free_all(inicial);
        parada = 1;
    }
    return 0;
}
