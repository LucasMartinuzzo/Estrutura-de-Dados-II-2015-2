#ifndef BUSCAS_H
#define	BUSCAS_H

#include "tads.h"

ListaP criaLista();

int inserirPalavrasBusca(ListaP, char*, int);

void imprimirListaBusca(ListaP);

void buscarComAspas(Palavra, Palavra, int);

void buscarSemAspas(Palavra, Palavra, int);

void buscarComAspasEnc(BancoPalavras*, Palavra);

void buscarSemAspasEnc(BancoPalavras*, Palavra);

void buscarEncadeado(BancoPalavras*,ListaP);

void buscarComAspasLinDup(BancoPalavrasLinear*, Palavra, char);

void buscarSemAspasLinDup(BancoPalavrasLinear*, Palavra, char);

void buscarLinearDuplo(BancoPalavrasLinear*, ListaP, char);

void liberarListaBusca(ListaP);

#endif	/* BUSCAS_H */