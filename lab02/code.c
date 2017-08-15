//Aluno Renan Clarindo Amorim
//RA: 186454

#include <stdio.h>
#include <stdlib.h>

struct NO {
    int indice;
    int usos;
    struct NO *proximo;
};

typedef struct NO NO;

//adiciona elementos na posição inicial da lista,
int adicionar (NO **lista, int indice){

    if (lista == NULL){
        NO *no = NULL;

        no = malloc (sizeof(NO));

        if(!no){
        	printf ("Erro de alocacao\n");
        	return 1;
        }

        no->indice = indice;
        no->usos = 0;
        no->proximo = NULL;

        *lista = no;
    } else {
        NO *no = NULL;

        no = malloc (sizeof(NO));

        no->indice = indice;
        no->usos = 0;
        no->proximo = *lista;

        *lista = no;
    }
}

void liberar (NO **lista){
	NO *j = *lista;
	NO *j_ant = j;
	while (j != NULL){
		j = j->proximo;
		free (j_ant);
		j_ant = j;
	}

	*lista = NULL;
}

int main(){

    int i = 0, tam_lista = 0, qtd_requisicoes = 0, custo = 0, custo_total = 0, mtf = 0, transp = 0, count = 0;
    int *requisicoes = NULL;
    NO *j = NULL, *j_ant = NULL, *j_ant2 = NULL, *lista = NULL, *aux = NULL;

    scanf ("%d", &tam_lista);
    scanf ("%d", &qtd_requisicoes);

    if (tam_lista > 1000 || tam_lista < 0|| qtd_requisicoes > 1000 || tam_lista < 0)
    	return 0;


    requisicoes = malloc (qtd_requisicoes*sizeof(int));

    for (i = 0; i < qtd_requisicoes; i++){
        scanf("%d", &requisicoes[i]);
    }

    for (i = tam_lista; i > 0; i--){
        if (adicionar (&lista, i) == 1){
        	return 1;  //erro de alocação
        }
    }



    // MTF

    for (i = 0; i < qtd_requisicoes; i++){
	    custo = 0;

	    for (j = lista, j_ant = NULL; j != NULL; j = j->proximo){
	    //	printf("2\n");

	    	custo++;
	    	if (j->indice == requisicoes[i]){

	    		if (j_ant != NULL){
	    			j_ant->proximo = j->proximo;
	    			j->proximo = lista;
	    			lista = j;
	    		}
	    	    break;
	    	}
	    	j_ant = j;
	    }
	    custo_total += custo;
	}

	mtf = custo_total;
	custo_total = 0;
	custo = 0;


	//recria a lista da forma original, para poder testar os outros métodos
	liberar (&lista);
	for (i = tam_lista; i > 0; i--){
        if (adicionar (&lista, i) == 1){
        	return 1;  //erro de alocação
        }
    }	

    // Transpose
	for (i = 0; i < qtd_requisicoes; i++){
	    custo = 0;

	    for (j = lista, j_ant = NULL, j_ant2 == NULL; j != NULL; j = j->proximo){
	    	custo++;
	    	if (j->indice == requisicoes[i]){
	    		if (j_ant != NULL && j_ant2 != NULL){ //3º elemento ou posterior da lista
	    			j_ant2->proximo = j_ant->proximo;
	    			j_ant->proximo = j->proximo;
	    			j->proximo = j_ant;
	    		} else if (j_ant == lista) { //2º elemento da lista
	      			lista->proximo = j->proximo;
	    			j->proximo = lista;
	    			lista = j;
	    		}
	    		break;
	    	}
	    	j_ant2 = j_ant;
	    	j_ant = j;

	    }
	    custo_total += custo;
	}  

	transp = custo_total;
	custo_total = 0;
	custo = 0;

	//recria a lista da forma original, para poder testar os outros métodos
	liberar (&lista);
	for (i = tam_lista; i > 0; i--){
        if (adicionar (&lista, i) == 1){
        	return 1;  //erro de alocação
        }
    }	

    //Count
    for (i = 0; i < qtd_requisicoes; i++){
	    custo = 0;

	    for (j = lista, j_ant = NULL; j != NULL; j = j->proximo){
	    //	printf("2\n");
	    	custo++;
	    	if (j->indice == requisicoes[i]){
	    		(j->usos)++;

	    		if (j_ant != NULL){
	    			for (aux = lista, j_ant2 = NULL; aux != NULL; aux = aux->proximo){
				    	if (aux->usos <= j->usos){
				    		if (j_ant2 != NULL){
				    			j_ant->proximo = j->proximo;
				    			j->proximo = j_ant2->proximo;
				    			j_ant2->proximo = j;
				    		} else if  (aux == lista){
				    			j_ant->proximo = j->proximo;
		    					j->proximo = aux;
		    					lista = j;
				    		}
				    	    break;
				    	}
				    	j_ant2 = aux;
				    }
	    		}

	    	    break;
	    	}
	    	j_ant = j;
	    }
	    custo_total += custo;
	}


	count = custo_total;
	custo_total = 0;
	custo = 0;

	printf ("%d %d %d\n", mtf, transp, count);

	//libera memória alocada
	liberar (&lista);
    free(requisicoes);

    return 0;
}
