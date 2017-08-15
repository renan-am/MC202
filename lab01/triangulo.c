// Aluno: Renan Clarindo Amorim
// RA: 186454

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main (){
    int i = 0, j = 0;
    int ordem = 0;
    double total = 0, media = 0, desvio_padrao = 0, aux = 0, soma_aux = 0;
    scanf ("%d", &ordem);

    double **M;

    M = malloc(ordem*sizeof(double*));
    if (!M){
        printf ("Erro de alocacao\n");
        return 1;
    }

// aloca memoria
    for (i = 0; i < ordem; i++){
        M[i] = malloc((i+1)*sizeof(double));
            if (!M[i]){
                if (!M){
                    printf ("Erro de alocacao\n");
                    return 1;
                }
            }
    }

//ler matriz
    for (i = 0; i < ordem; i++){
        for (j = 0; j < i+1; j++){
            scanf ("%lf", &M[i][j]);
        }
    }

//calcular média
    for (i = 0; i < ordem; i++){
        for (j = 0; j < i+1; j++){
            total = total + M[i][j];
        }
    }

    media = total/(((ordem*ordem)+ordem)/2);

//somatorio do valor interno a raiz do desvio padrao
    for (i = 0; i < ordem; i++){
        for (j = 0; j < i+1; j++){
            aux = M[i][j] - media;
            soma_aux = soma_aux + pow(aux, 2);
        }
    }

    aux = soma_aux/(((ordem*ordem)+ordem)/2);
    desvio_padrao = sqrt(aux);

//normaliza a funcao
    for (i = 0; i < ordem; i++){
        for (j = 0; j < i+1; j++){
            M[i][j] = (M[i][j]-media)/desvio_padrao;
        }
    }


//imprime matriz
    for (i = 0; i < ordem; i++){
        for (j = 0; j < i+1; j++){
            printf ("%.12lf ", M[i][j]);
        }
        printf ("\n");
    }
// imprime media desvio_padrao
    printf("\n%.12lf %.12lf \n", media, desvio_padrao);

// liberar memoria
    for (i = 0; i < ordem; i++)
        free (M[i]);

    free (M);
return 0;
}
