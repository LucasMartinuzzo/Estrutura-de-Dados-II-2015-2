#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"
#include "linear.h"

BancoPalavrasLinear *criaBancoLinear (){
    BancoPalavrasLinear *aux;
    int i;
    aux = (BancoPalavrasLinear*)malloc (sizeof(BancoPalavrasLinear));
    if (aux == NULL){
        printf ("Nao foi possivel alocar memoria.\n");
        return NULL;
    }
    QUANTIDADE(aux) = 0;
    for (i = 0; i < MAXLINEAR; i++){
        inicializarPalavra(&(LISTA(aux)[i]));
    }
    return aux;
}

int posicaoPalavraLinear (BancoPalavrasLinear *bancoL, char *palavra, int indice){
    if(QUANTIDADE(bancoL) == 0)
        return indice;
    int i;
    Palavra p_W = (LISTA(bancoL))[indice];
    for(i = indice;p_W != NULL && i != indice -1;){
        if(strcmp(palavra,CONTEUDO(p_W)) == 0)
            return i;
        if(i == (MAXLINEAR - 1)){
            if(indice == 0)
                break;
            else
                i = 0;
        }
        else
            i++;
        p_W = (LISTA(bancoL))[i];
    }
    return i;
}

int inserirPalavraLinear(BancoPalavrasLinear *bancoL, char *palavra, int posicao, char *fonte){
    int indice,i;
    indice = calcularIndice(palavra,MAXLINEAR);
    if(QUANTIDADE(bancoL) == MAXLINEAR){
        printf("O banco de palavras esta cheio.\n");
        return -1;
    }
    if(indice == -1){
        printf ("Nao foi possivel inserir a palavra (indice invalido).\n");
        return -1;
    }
    i = posicaoPalavraLinear(bancoL,palavra,indice);
    Palavra p_W = (LISTA(bancoL))[i];
    if(p_W == NULL){
        Palavra auxP;
        alocarPalavra(&auxP,palavra,posicao,fonte);
        LISTA(bancoL)[i] = auxP;
        QUANTIDADE(bancoL)++;
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

void imprimirTudoLinear (BancoPalavrasLinear *bancoL){
    int i;
    Palavra W;
    ListaF F;
    Posicoes P;
    if(QUANTIDADE(bancoL) == 0){
        printf("Vazio\n");
        return;
    }
    for(i=0;i<MAXLINEAR;i++){
        W = LISTA(bancoL)[i];
        if(W != NULL) {
            printf("%d - %s:\n",i, CONTEUDO(W));
            F = FONTE(W);
            for(;F!=NULL;F = POST(F)){
                printf("%s: ",CONTEUDO(F));
                P = POSICOES(F);
                for(;P!=NULL;P = POST(P))
                    printf("%d ",CONTEUDO(P));
                printf("\n");
                }
            printf("\n");
        }
    }
}

void liberarTudoLinear (BancoPalavrasLinear *bancoL){
    int i;
    Palavra W, auxW;
    ListaF F, auxF;
    Posicoes P, auxP;
    if(QUANTIDADE(bancoL) == 0){
        free(bancoL);
        return;
    }
    for(i=0;i<MAXLINEAR;i++){
        W = LISTA(bancoL)[i];
        if(W != NULL) {
            F = FONTE(W);
            for(;F!=NULL;){
                P = POSICOES(F);
                for(;P!=NULL;){
                    auxP = P;
                    P = POST(P);
                    free(auxP);
                }
                auxF = F;
                F = POST(F);
                free(auxF);
            }
            auxW = W;
            W = POST(W);
            free(auxW);
        }
    }
    free(bancoL);
    return;
}
