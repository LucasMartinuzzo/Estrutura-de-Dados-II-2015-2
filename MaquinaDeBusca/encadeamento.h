#ifndef ENCADEAMENTO_H
#define	ENCADEAMENTO_H

#include "tads.h"

#define MAX 100003
#define LISTA(L) ((L)->lista)

typedef struct{
    ListaP lista [MAX];
}BancoPalavras;

BancoPalavras *criaBanco();

int calcularIndice();

Palavra buscarPalavra();

int inserirPalavra();

void imprimirTudo();

void liberarTudo ();

#endif	/* ENCADEAMENTO_H */