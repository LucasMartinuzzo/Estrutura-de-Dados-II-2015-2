#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "bucketsort.h"

int sort (int*vet, int tam){
    return 1;
}

int bubblesort (int *vet, int tam){
    int i, j, aux, k = tam -1;
    int flag;
    for (i=0;i<tam;i++){
        flag = 1;
        for(j=0;j<k;j++){
            if(vet[j] > vet[j+1]){
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
                flag = 0;
            }
        }
        k--;
        if(flag)
            break;
    }
    return 1;
}

int shakesort (int *vet, int tam){
    int i, aux;
    int flag = 1;
    int top = tam -1;
    int bot = 0;
    while(flag && bot < top){
        flag = 0;
        for(i= bot;i<top;i++){
            if(vet[i] > vet[i+1]){
                aux = vet[i];
                vet[i]= vet[i+1];
                vet[i+1] = aux;
                flag = 1;
            }
        }
        top--;
        for(i=top;i>bot;i--){
            if(vet[i-1] > vet[i]){
                aux = vet[i-1];
                vet[i-1] = vet[i];
                vet[i] = aux;
                flag = 1;
            }
        }
        bot++;
    }
    return 1;
}

int insertionsort (int *vet, int tam){
    int i, j, aux;
    for(i=1;i<tam;i++){
        aux = vet[i];
        j = i-1;
        while((j>=0) && (aux < vet[j])){
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = aux;
    }
    return 1;
}

int shellsort (int *vet, int tam){
    int i, j, aux;
    int gap = 1;
    while(gap < tam){
        gap = 3*gap+1;
    }
    while(gap > 1){
        gap /= 3;
        for(i=gap;i<tam;i++){
            aux = vet[i];
            j = i - gap;
            while((j>=0) && (aux < vet[j])){
                vet[j+gap] = vet[j];
                j-= gap;
            }
            vet[j+gap] = aux;
        }
    }
    return 1;
}

int selectionsort (int *vet, int tam){
    int i, j, min, aux;
    for(i=0;i<tam-1;i++){
        min = i;
        for(j=i+1;j<tam;j++){
            if(vet[j] < vet[min])
                min = j;
        }
        if(i != min){
            aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
        }
    }
    return 1;
}

int ranksort (int *vet, int tam){
    int i,j;
    int rankVet[1000001];
    for(i=0;i<=1000000;i++)
        rankVet[i] = 0;
    for(i=0;i<tam;i++){
        rankVet[vet[i]]++;
    }
    for(i=0,j=0;i<=1000000 && j<tam;i++){
        while(rankVet[i]>0){
            vet[j] = i;
            j++;
            rankVet[i]--;
        }
    }
    return 1;
}
int quicksortPrimeiro (int *vet, int limEsquerdo, int limDireito){
    int i, j, pivot, aux;
    i = limEsquerdo;
    j = limDireito;
    pivot = vet[i];
    while(i <= j){
        while(vet[i] < pivot && i < limDireito)
            i++;
        while(vet[j] > pivot && j > limEsquerdo)
            j--;
        if(i <= j){
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    }
    if(j > limEsquerdo)
        quicksortPrimeiro(vet,limEsquerdo,j);
    if(i < limDireito)
        quicksortPrimeiro(vet,i,limDireito);
    return 1;
}

int quicksortCentral (int *vet, int limEsquerdo, int limDireito){
    int i, j, pivot, aux;
    i = limEsquerdo;
    j = limDireito;
    pivot = vet[(i + j)/2];
    while(i <= j){
        while(vet[i] < pivot && i < limDireito)
            i++;
        while(vet[j] > pivot && j > limEsquerdo)
            j--;
        if(i <= j){
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    }
    if(j > limEsquerdo)
        quicksortCentral(vet,limEsquerdo,j);
    if(i < limDireito)
        quicksortCentral(vet,i,limDireito);
    return 1;
}

int quicksortAleatorio (int *vet, int limEsquerdo, int limDireito){
    int i, j, pivot, aux;
    i = limEsquerdo;
    j = limDireito;
    srand(time(NULL));
    pivot = vet[i + rand()%(j - i)];
    while(i <= j){
        while(vet[i] < pivot && i < limDireito)
            i++;
        while(vet[j] > pivot && j > limEsquerdo)
            j--;
        if(i <= j){
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    }
    if(j > limEsquerdo)
        quicksortAleatorio(vet,limEsquerdo,j);
    if(i < limDireito)
        quicksortAleatorio(vet,i,limDireito);
    return 1;
}

int quicksortMediana (int *vet, int limEsquerdo, int limDireito){
    int i, j, pivot, aux;
    i = limEsquerdo;
    j = limDireito;
    pivot = (vet[i] + vet[j] + vet[(i+j)/2]) / 3;
    while(i <= j){
        while(vet[i] < pivot && i < limDireito)
            i++;
        while(vet[j] > pivot && j > limEsquerdo)
            j--;
        if(i <= j){
            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            i++;
            j--;
        }
    }
    if(j > limEsquerdo)
        quicksortMediana(vet,limEsquerdo,j);
    if(i < limDireito)
        quicksortMediana(vet,i,limDireito);
    return 1;
}

int mergesort (int *vet, int posInicio, int posFim){
    int i, j, aux, metadeTam, *mergeVet;
    if(posInicio == posFim) return 1;
    metadeTam = (posInicio + posFim)/2;
    mergesort(vet,posInicio,metadeTam);
    mergesort(vet,metadeTam + 1,posFim);
    i = posInicio;
    j = metadeTam + 1;
    aux = 0;
    mergeVet = (int *)malloc(sizeof(int)*(posFim-posInicio+1));
    while(i <= metadeTam || j <= posFim){
        if(i == metadeTam+1){
            mergeVet[aux] = vet[j];
            j++;
            aux++;
        }
        else if(j == posFim+1){
            mergeVet[aux] = vet[i];
            i++;
            aux++;
        }
        else if(vet[i] < vet[j]){
            mergeVet[aux] = vet[i];
            i++;
            aux++;
        }
        else{
            mergeVet[aux] = vet[j];
            j++;
            aux++;
        }
    }
    for(i=posInicio;i<=posFim;i++)
        vet[i] = mergeVet[i - posInicio];
    free(mergeVet);
    return 1;
}

int heapsort (int vet[], int tam){
    int i, n, pai, filho, aux;
    i = tam/2;
    n = tam;
    while(1){
        if(i>0){
            i--;
            aux = vet[i];
        }
        else {
            n--;
            if(n == 0) return 1;
            aux = vet[n];
            vet[n] = vet[0];
        }
        pai = i;
        filho = i*2 +1;
        while(filho < n){
            if((filho + 1) < n && vet[filho+1] > vet[filho])
                filho++;
            if(vet[filho] > aux){
                vet[pai] = vet[filho];
                pai = filho;
                filho = pai*2 + 1;
            }
            else 
                break;
        }
        vet[pai] = aux;
    }
    return 1;
}

int radixsort(int vet[], int tam){
    int lim, mask;
    mask = 1;
    lim = INT_MAX/mask;
    while(lim > 2){
        if(bucketsort(vet,tam, mask) == -1) printf("erro\n");
        mask*=10;
        lim = INT_MAX/mask;
    }
    bucketsort(vet,tam,mask);
    return 1;
}
int radixsortBin(int vet[], int tam){
    int shift, mask;
    mask = 1;
    shift = 0;
    while(shift < 32){
        /*printf("mask: %d shift: %d\n",mask, shift);*/
        bucketsortBin(vet,tam,mask,shift);
        shift++;
        mask = mask << 1;
    }
    return 1;
}