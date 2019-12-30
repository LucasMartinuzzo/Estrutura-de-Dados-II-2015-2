#include <stdio.h>
#include <stdlib.h>
#include "nn2opt.h"
#include "exato.h"

bool cidadeVisitada (int nCidades, int *percurso, int cidadeAtual){
    int i;
    for (i = 0; i<nCidades; i++)
        if (percurso[i] == cidadeAtual)
            return true;
    return false;
}

int *inicializarPercurso (int nCidades){
    int *percurso = (int*)malloc(nCidades*sizeof(int));
    if(!percurso)
        exit(1);
    int i;
    for (i=0; i<nCidades; i++)
        percurso[i] = -1;
    return percurso;
}

void vizinhoMaisProximo (int nCidades, int **matrizDistancias, int *percurso){
    int i = 0, j, k, menorDistancia = -1, nn;
    percurso[0] = 0;
    for (k = 1; k<nCidades; ){
        for (j = 0; j<nCidades; j++){
            if ((i != j) && ((matrizDistancias[i][j] < menorDistancia)|| menorDistancia== -1) && (!cidadeVisitada (nCidades, percurso, j))){
                menorDistancia = matrizDistancias[i][j];
                nn = j;
            }
        }
        percurso[k] = nn;
        k++;
        i = nn;
        menorDistancia = 9999;
    }
}

void inverter (int *percurso, int inicio, int fim){
    int i, temp;
    for (i=1; i<=(fim-inicio)/2; i++){
        temp = percurso[inicio+i];
        percurso[inicio+i] = percurso[fim-i];
        percurso[fim-i] = temp;
    }
}

void opt2 (int nCidades, int **matrizDistancias, int *percurso, int *distancia){
    int i,j, k, distanciaAtual = *distancia, *menorPercurso = (int*)malloc(nCidades*sizeof(int));
    int distanciaOriginal = *distancia;
    if(!menorPercurso)
        exit(1);
    for (i=0; i<=nCidades-2; i++)
        for (j=i+2; j<nCidades; j++){
            trocar(&percurso[i+1], &percurso[j]);
            inverter (percurso, i+1, j);
            distanciaAtual = calcularDistancia (nCidades, matrizDistancias, percurso);
            if (distanciaAtual < *distancia){
                *distancia = distanciaAtual;
                for (k=0; k<nCidades; k++)
                    menorPercurso[k] = percurso[k];
            }
            trocar(&percurso[i+1], &percurso[j]);
            inverter (percurso, i+1, j);
        }
    if(distanciaOriginal != *distancia)
        for (i=0; i<nCidades; i++)
            percurso[i] = menorPercurso[i];
}
