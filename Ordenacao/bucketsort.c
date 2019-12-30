#include <stdio.h>
#include <stdlib.h>
#include "bucketsort.h"

int bucketsort(int vet[], int tam, int mask){
    int i,j, tmp;
    Fila *bucket[10];
    for(i=0;i<10;i++){
        bucket[i] = criarFila();
    }
    for(i=0;i<tam;i++){
        inserir(bucket[(vet[i]/mask)%10],vet[i]);
    }
    for(i=0,j=0;i<tam;){
        tmp = retirar(bucket[j]);
        if(tmp!=-1){
            vet[i] = tmp;
            i++;
        }
        else{
            j++;
        }
    }
    for(i=0;i<10;i++){
        liberar(bucket[i]);
    }
    return 1;
}

int bucketsortBin(int vet[], int tam, int mask, int shift){
    int i,j,tmp;
    Fila *bucket[2];
    for(i=0;i<2;i++)
        bucket[i] = criarFila();
    for(i=0;i<tam;i++){
        inserir(bucket[(vet[i] & mask)>>shift], vet[i]);
    }
    for(i=0,j=0;i<tam;){
        tmp = retirar(bucket[j]);
        if(tmp!=-1){
            vet[i] = tmp;
            i++;
        }
        else{
            j++;
        }
    }
    for(i=0;i<2;i++){
        liberar(bucket[i]);
    }
    return 1;
}

Fila *criarFila (){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}
No *inserirFim (No* fim, int conteudo){
    No *p = (No*)malloc(sizeof(No));
    p->conteudo = conteudo;
    p->proximo = NULL;
    if(fim !=NULL){
        fim->proximo = p;
    }
    return p;
}

No *retirarInicio (No* inicio){
    No *p;
    p = inicio->proximo;
    free(inicio);
    return p;
}
void inserir(Fila *f, int conteudo){
    f->fim = inserirFim(f->fim,conteudo);
    if(f->inicio == NULL)
        f->inicio = f->fim;
    
}
int retirar (Fila *f){
    int conteudo;
    if(vazia(f)){
        return -1;
    }
    conteudo = f->inicio->conteudo;
    f->inicio = retirarInicio(f->inicio);
    if(f->inicio == NULL)
        f->fim = NULL;
    return conteudo;
}
int vazia (Fila *f){
    return (f->inicio == NULL);
}
void liberar (Fila *f){
    No *q = f->inicio;
    No* t;
    while(q!=NULL){
        t = q->proximo;
        free(q);
        q=t;
    }
    free(f);
}
