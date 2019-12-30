#include <stdio.h>
#include <stdlib.h>
#include "exato.h"

int** criarMatrizDistancias (int nCidades){
    int **distancias = (int**)malloc(nCidades*sizeof(int*));
    if(!distancias)
        exit(1);    
    int i, j;
    for (i=0; i<nCidades; i++){
        distancias[i] = (int*)malloc(nCidades*sizeof(int));
        if(!distancias[i])
            exit(1);
        for(j=0; j<nCidades; j++){
            scanf("%d",&distancias[i][j]);
        }
    }
    return distancias;
}

void imprimir (int n, int** matriz){
    int i,j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

void trocar (int *cidadeA, int *cidadeB){
    int temp;
    temp = *cidadeA;
    *cidadeA = *cidadeB;
    *cidadeB = temp;
}

void compararMenorPercurso (int nCidades, int **matrizDistancias, int *menorDistancia, int *menorPercurso, int *percursoAtual){
    int distanciaAtual = calcularDistancia(nCidades, matrizDistancias, percursoAtual);
    int i;
    if(distanciaAtual < *menorDistancia){
        for (i=0;i<nCidades;i++){
            menorPercurso[i] = percursoAtual[i];
        }
        *menorDistancia = distanciaAtual;
    }
}

void metodoExato (int nCidades, int **matrizDistancias, int *menorDistancia, int *menorPercurso, int *percursoAtual, int inicio, int fim){
    int i;
    if(inicio == fim){
        compararMenorPercurso(nCidades, matrizDistancias, menorDistancia, menorPercurso, percursoAtual);
    }
    else {
        for(i=inicio; i<=fim; i++){
            trocar((percursoAtual + inicio),(percursoAtual + i));
            metodoExato(nCidades, matrizDistancias, menorDistancia, menorPercurso, percursoAtual,(inicio + 1), fim);
        }
    }
}

int calcularDistancia (int nCidades, int **matrizDistancias, int *percurso){
    int i, distancia = 0;
    for(i=0;i<nCidades - 1;i++)
        distancia+=matrizDistancias[percurso[i]] [percurso[i+1]];
    if(nCidades != 1)
        distancia+=matrizDistancias[percurso[i]] [percurso[0]];
    return distancia;
}

void imprimirResultado (int nCidades, int menorDistancia, int*menorPercurso){
    int i;
    for (i=0;i<nCidades;i++)
        printf("%d\n\n",menorPercurso[i]);
    printf("%d\n\n*\n",menorDistancia);
}

int *criarPercursoInicial (int nCidades){
    int i;
    int *percurso = (int*)malloc(nCidades*sizeof(int));
    if(!percurso)
        exit(1);
    for(i=0;i<nCidades;i++)
        percurso[i] = i;
    return percurso;
}