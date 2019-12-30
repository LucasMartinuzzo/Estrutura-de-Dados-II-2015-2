#ifndef LINEAR_H
#define	LINEAR_H

#include "tads.h"
#include "encadeamento.h"

#define MAXLINEAR 1000003

typedef struct{
    Palavra lista [MAXLINEAR];
    int quantidade;
}BancoPalavrasLinear;

BancoPalavrasLinear *criaBancoLinear();

int posicaoPalavraLinear();

int inserirPalavraLinear();

void imprimirTudoLinear();

void liberarTudoLinear ();


#endif	/* LINEAR_H */