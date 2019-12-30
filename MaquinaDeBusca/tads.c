#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"

void inicializarPosicao (Posicoes *p_P){
    *p_P = NULL;
    return;
}

void inicializarPalavra (Palavra *p_W){
    *p_W = NULL;
    return;
}

void inicializarLista (ListaP *p_L){
    *p_L = NULL;
    return;
}

void inicializarFonte(ListaF *p_F){
    *p_F = NULL;
    return;
}

int alocarPosicao(Posicoes *p_L, int posicao){
    Posicoes pos = (Posicoes) malloc(sizeof (Celula));
    if (pos == NULL) return -1;
    CONTEUDO(pos) = posicao;
    POST(pos) = NULL;
    *p_L = pos;
    return 1;
}

int alocarFonte(ListaF *p_F, int posicao, char *fonte){
    ListaF F = (ListaF) malloc(sizeof(mListaF));
    if(F == NULL) return -1;
    CONTEUDO(F) = fonte;
    Posicoes pos = NULL;
    if(posicao != -999)
        alocarPosicao(&pos,posicao);
    POSICOES(F) = pos;
    POST(F) = NULL;
    *p_F = F;
    return 1;
}

int alocarPalavra (Palavra *p_L, char *palavra, int posicao, char*fonte){
    Palavra L = (Palavra) malloc(sizeof(mPalavra));
    if(L == NULL) return -1;
    CONTEUDO(L) = palavra;
    ListaF F;
    if(strcmp(fonte," ") == 0){
        FONTE(L) = NULL;
        POST(L) = NULL;
        *p_L = L;
        return 1;
    }
    alocarFonte(&F,posicao,fonte);
    if(F == NULL) {
        free(*p_L);
        *p_L = NULL;
        return -2;
    }
    FONTE(L) = F;
    POST(L) = NULL;
    *p_L = L;
    return 1;
}

int alocarLista(ListaP *p_L){
    ListaP L = (ListaP) malloc (sizeof(mListaP));
    if(L == NULL) return -1;
    QUANTIDADE(L) = 0;
    PALAVRAS(L) = NULL;
    *p_L = L;
    return 1;
}