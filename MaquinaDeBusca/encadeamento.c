#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"

BancoPalavras *criaBanco (){
    BancoPalavras *aux;
    int i;
    aux = (BancoPalavras*)malloc (sizeof(BancoPalavras));
    if (aux == NULL){
        printf ("Nao foi possivel alocar memoria.\n");
        return NULL;
    }
    for (i = 0; i < MAX; i++){
        inicializarLista(&(LISTA(aux)[i]));
        alocarLista(&(LISTA(aux)[i]));
    }
    return aux;
}

int calcularIndice (char *palavra, int tam){
    int i, indice = 0;
    indice = palavra[0];
    if(strlen(palavra) > 1){
        indice = palavra[0]*palavra[1];
    for (i = 2; i < strlen (palavra); i++)
        indice += palavra[i]*palavra[i-1]*palavra[i-2];
    }
    indice = indice % tam;
    if (indice < 0)
        return -1;
    return indice;
}

Palavra buscarPalavra(BancoPalavras *banco, char *palavra, int indice){
    ListaP p_L = (LISTA(banco))[indice];
    if(QUANTIDADE(p_L) == 0)
        return NULL;
    else{
        Palavra p_W = PALAVRAS(p_L);
        for(;p_W != NULL; p_W = POST(p_W))
            if(strcmp(palavra,CONTEUDO(p_W)) == 0)
               return p_W;
            else if(strcmp(palavra,CONTEUDO(p_W)) < 0)
                return NULL;
    }
    return NULL;
}

int inserirPalavra(BancoPalavras *banco, char *palavra, int posicao, char *fonte){
    int indice;
    indice = calcularIndice(palavra,MAX);
    if(indice == -1){
        printf ("Nao foi possivel inserir a palavra (indice invalido).\n");
        return -1;
    }
    ListaP p_L = (LISTA(banco))[indice];
    Palavra p_W = PALAVRAS(p_L);
    Palavra auxP = buscarPalavra(banco,palavra,indice);
    if(QUANTIDADE(p_L) == 0){
        alocarPalavra(&auxP,palavra,posicao,fonte);
        QUANTIDADE(p_L) = 1;
        PALAVRAS(p_L) = auxP;
    }else if(auxP == NULL){
        alocarPalavra(&auxP,palavra,posicao,fonte);
        if(strcmp(palavra,CONTEUDO(p_W)) < 0){
            POST(auxP) = p_W;
            PALAVRAS(p_L) = auxP;
            QUANTIDADE(p_L)++;
            return 1;
        }
        while(POST(p_W) != NULL && strcmp(palavra,CONTEUDO(POST(p_W))) > 0)
            p_W = POST(p_W);
        POST(auxP) = POST(p_W);
        POST(p_W) = auxP;
        QUANTIDADE(p_L)++;
    }
    else{
        ListaF fontes = FONTE(auxP);
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

void imprimirTudo (BancoPalavras *banco){
    int i,j= 0;
    ListaP L;
    Palavra W;
    ListaF F;
    Posicoes P;
    for(i=0;i<MAX;i++){
        L = LISTA(banco)[i];
        if(QUANTIDADE(L) > 0){
            printf("%d:\n",i);
            W = PALAVRAS(L);
            for(;W!=NULL;W=POST(W)){
                printf("%s\n",CONTEUDO(W));
                F = FONTE(W);
                for(;F!=NULL;F = POST(F)){
                    printf("%s: ",CONTEUDO(F));
                    P = POSICOES(F);
                    for(;P!=NULL;P = POST(P)){
                        j++;
                        printf("%d ",CONTEUDO(P));
                    }
                    printf("\n");
                }
                printf("\n");
           }
        }
    }
    printf("%d\n",j);
}

void liberarTudo (BancoPalavras *banco){
    int i;
    ListaP L;
    Palavra W, antW;
    ListaF F, antF;
    Posicoes P, antP;
    for(i=0;i<MAX;i++){
        L = LISTA(banco)[i];
        if(QUANTIDADE(L) > 0){
            W = PALAVRAS(L);
            for(;W!=NULL;){
                F = FONTE(W);
                for(;F!=NULL;){
                    P = POSICOES(F);
                    for(;P!=NULL;){
                        antP = P;
                        P = POST(P);
                        free(antP);
                    }
                    antF = F;
                    F = POST(F);
                    free(antF);
                }
                antW = W;
                W = POST(W);
                free(antW);
           } 
        }
        free(L);
    }
    free(banco);
}