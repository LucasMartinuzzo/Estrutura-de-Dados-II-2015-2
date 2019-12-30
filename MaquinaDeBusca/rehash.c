#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"
#include "linear.h"
#include "rehash.h"

int calcularIndiceDuplo(char *palavra, int indice, int tam){
    int i, indiceD;
    indiceD = palavra[0];
    if(strlen(palavra) > 1){
        indiceD = palavra[0]*palavra[1];
    for (i = 2; i < strlen (palavra); i++)
        indiceD += palavra[i]*palavra[i-1]*palavra[i-2];
    }
    indiceD = 1 + indice % (tam -1);
    indiceD = (indice + indiceD) % tam;
    if (indiceD < 0)
        return -1;
    return indiceD;
}

int posicaoPalavraDuplo (BancoPalavrasLinear *bancoD, char *palavra, int indice){
    if(QUANTIDADE(bancoD) == 0)
        return indice;
    int i;
    Palavra p_W = (LISTA(bancoD))[indice];
    for(i = indice;p_W != NULL;){
        if(strcmp(palavra,CONTEUDO(p_W)) == 0)
            return i;
        else
            i = calcularIndiceDuplo(palavra,i,MAXLINEAR);
        p_W = (LISTA(bancoD))[i];
    }
    return i;
}

int inserirPalavraDuplo(BancoPalavrasLinear *bancoD, char *palavra, int posicao, char *fonte){
    int indice,i;
    indice = calcularIndice(palavra,MAXLINEAR);
    if(QUANTIDADE(bancoD) == MAXLINEAR){
        printf("O banco de palavras esta cheio.\n");
        return -1;
    }
    if(indice == -1){
        printf ("Nao foi possivel inserir a palavra (indice invalido).\n");
        return -1;
    }
    i = posicaoPalavraDuplo(bancoD,palavra,indice);
    Palavra p_W = (LISTA(bancoD))[i];
    if(p_W == NULL){
        Palavra auxP;
        alocarPalavra(&auxP,palavra,posicao,fonte);
        LISTA(bancoD)[i] = auxP;
        QUANTIDADE(bancoD)++;
    }
    else{
        ListaF fontes = FONTE(p_W);
        for(;POST(fontes) !=NULL;fontes = POST(fontes))
            if(strcmp(fonte,CONTEUDO(fontes)) == 0)
                break;
        if(strcmp(fonte,CONTEUDO(fontes)) == 0){
            Posicoes posicoes = POSICOES(fontes);
            Posicoes auxPos = NULL;
            for(;POST(posicoes) != NULL;posicoes = POST(posicoes));
            alocarPosicao(&auxPos,posicao);
            POST(posicoes) = auxPos;
        }
        else{
            ListaF auxF;
            alocarFonte(&auxF,posicao,fonte);
            POST(fontes) = auxF;
        }
    }
    return 1;
}