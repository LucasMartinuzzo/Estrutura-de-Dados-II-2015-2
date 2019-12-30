#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

enum entrada {BUBBLE = 1, SHAKE, INSERTION, SHELL, SELECTION, RANK,
QUICKPRIMEIRO, QUICKCENTRAL, QUICKRANDOM, QUICKMEDIANA, MERGE, HEAP,
RADIX, RADIXBIN};

int opcoes (char* opcao){
    if(strcmp(opcao,"bubble") == 0)
        return BUBBLE;
    if(strcmp(opcao,"shake") == 0)
        return SHAKE;
    if(strcmp(opcao,"insertion") == 0)
        return INSERTION;
    if(strcmp(opcao,"shell") == 0)
        return SHELL;
    if(strcmp(opcao,"selection") == 0)
        return SELECTION;
    if(strcmp(opcao,"rank") == 0)
        return RANK;
    if(strcmp(opcao,"quickprimeiro") == 0)
        return QUICKPRIMEIRO;
    if(strcmp(opcao,"quickcentral") == 0)
        return QUICKCENTRAL;
    if(strcmp(opcao,"quickrandom") == 0)
        return QUICKRANDOM;
    if(strcmp(opcao,"quickmediana3") == 0)
        return QUICKMEDIANA;
    if(strcmp(opcao,"merge") == 0)
        return MERGE;
    if(strcmp(opcao,"heap") == 0)
        return HEAP;
    if(strcmp(opcao,"radix") == 0)
        return RADIX;
    if(strcmp(opcao,"radixbin") == 0)
        return RADIXBIN;
    return 0;
}

int* criaVetor(int n){
    int *vet = (int*)malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++)
        scanf("%d\n",&vet[i]);
    return vet;
}
void imprimir(int *vet, int n){
    int i;
    for(i=0;i<n;i++)
        printf("%d\n",vet[i]);
}

int main(int argc, char** argv) {
    int tam = atoi(argv[2]);
    int *vetor = criaVetor(tam);
    int opcao = opcoes(argv[1]);
    switch(opcao){
        case BUBBLE:
            bubblesort(vetor,tam);
            break;
        case SHAKE:
            shakesort(vetor,tam);
            break;
        case INSERTION:
            insertionsort(vetor,tam);
            break;
        case SHELL:
            shellsort(vetor,tam);
            break;
        case SELECTION:
            selectionsort(vetor,tam);
            break;
        case RANK:
            ranksort(vetor,tam);
            break;
        case QUICKPRIMEIRO:
            quicksortPrimeiro(vetor,0,tam-1);
            break;
        case QUICKCENTRAL:
            quicksortCentral(vetor,0,tam-1);
            break;
        case QUICKRANDOM:
            quicksortAleatorio(vetor,0,tam-1);
            break;
        case QUICKMEDIANA:
            quicksortMediana(vetor,0,tam-1);
            break;
        case MERGE:
            mergesort(vetor,0,tam-1);
            break;
        case HEAP:
            heapsort(vetor,tam);
            break;
        case RADIX:
            radixsort(vetor,tam);
            break;
        case RADIXBIN:
            radixsortBin(vetor,tam);
            break;
        default:
            break;
    }
    imprimir(vetor,tam);
    free(vetor);
    return (EXIT_SUCCESS);
}

