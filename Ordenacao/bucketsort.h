#ifndef BUCKETSORT_H
#define	BUCKETSORT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int conteudo;
    struct No* proximo;
}No;

typedef struct{
    No *inicio;
    No *fim;
}Fila;
int bucketsort(int*,int,int);
int bucketsortBin(int*,int,int,int);

Fila *criarFila ();
No *inserirFim (No*, int);
No *retirarInicio (No*);
void inserir(Fila*, int);
int retirar (Fila*);
int vazia (Fila *);
void liberar (Fila*);


#endif	/* BUCKETSORT_H */

