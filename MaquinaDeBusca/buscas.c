#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"
#include "linear.h"
#include "rehash.h"
#include "buscas.h"

ListaP criaLista(){
    ListaP aux;
    alocarLista(&aux);
    return aux;
}

int inserirPalavrasBusca(ListaP listaBusca, char *palavra, int linha){
    Palavra aux, p_W = PALAVRAS(listaBusca);
    if(!alocarPalavra(&aux,palavra,linha," "))
        return 0;
    if(p_W == NULL){
        PALAVRAS(listaBusca) = aux;
        return 1;
    }
    for(;POST(p_W) != NULL;p_W = POST(p_W));
    POST(p_W) = aux;
    return 1;    
}

void imprimirListaBusca (ListaP listaBusca){
    Palavra W = PALAVRAS(listaBusca);
    ListaF F;
    if(QUANTIDADE(listaBusca) == 0){
        printf("Vazio\n");
        return;
    }
    for(;W != NULL; W =POST(W)){
        printf("%s\n", CONTEUDO(W));
        F = FONTE(W);
        for(;F!=NULL;F = POST(F))
            printf("%s ",CONTEUDO(F));
        printf("\n");
    }
}

void liberarListaBusca (ListaP listaBusca){
    Palavra W = PALAVRAS(listaBusca), auxW;
    ListaF F, auxF;
    Posicoes P, auxP;
    if(QUANTIDADE(listaBusca) == 0){
        free(listaBusca);
        return;
    }
    for(;W != NULL;){
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
    free(listaBusca);
    return;
}

void buscarComAspas(Palavra pesquisa, Palavra W, int numPalavras){
    ListaF fontes, auxF, fontePesquisa, antFontePesquisa;
    Posicoes posicoes, auxP, P;
    int fonteEncontrada = 0, count;
    if(numPalavras == 1){
        auxF = FONTE(W);
        auxP = POSICOES(auxF);
        alocarFonte(&fontes,CONTEUDO(auxP),CONTEUDO(auxF));
        FONTE(pesquisa) = fontes;
        posicoes = POSICOES(fontes);
        for(auxP = POST(auxP); auxP!=NULL; auxP = POST(auxP),posicoes = POST(posicoes)){
            alocarPosicao(&P,CONTEUDO(auxP));
            POST(posicoes) = P;
        }
        for(fontePesquisa = FONTE(pesquisa), auxF = POST(auxF);auxF != NULL;fontePesquisa = POST(fontePesquisa),auxF = POST(auxF)){
            auxP = POSICOES(auxF);
            alocarFonte(&fontes,CONTEUDO(auxP),CONTEUDO(auxF));
            POST(fontePesquisa) = fontes;
            posicoes = POSICOES(fontes);
            for(auxP = POST(auxP); auxP!=NULL; auxP = POST(auxP),posicoes = POST(posicoes)){
                alocarPosicao(&P,CONTEUDO(auxP));
                POST(posicoes) = P;
            }
        }
    }
    else{
        for(count = 0, fontePesquisa = FONTE(pesquisa);fontePesquisa != NULL;){
            for(auxF = FONTE(W);auxF != NULL; auxF = POST(auxF)){
                if(strcmp(CONTEUDO(fontePesquisa),CONTEUDO(auxF)) == 0){
                    for(posicoes = POSICOES(fontePesquisa);posicoes != NULL; posicoes = POST(posicoes)){
                        for(auxP = POSICOES(auxF);auxP != NULL; auxP = POST(auxP)){
                            if(CONTEUDO(auxP) == (CONTEUDO(posicoes) + numPalavras - 1)){
                                fonteEncontrada = 1;
                                break;
                            }
                        }
                        if(fonteEncontrada == 1)
                            break;
                    }
                    if(fonteEncontrada == 1)
                        break;
                }
            }
            if(fonteEncontrada == 0 && count == 0){
                FONTE(pesquisa) = POST(fontePesquisa);
                free(fontePesquisa);
                fontePesquisa = FONTE(pesquisa);
                antFontePesquisa = FONTE(pesquisa);
            }
            else if(fonteEncontrada == 0){
                POST(antFontePesquisa) = POST(fontePesquisa);
                free(fontePesquisa);
                fontePesquisa = POST(antFontePesquisa);
                count++;
            }
            else{
                antFontePesquisa = fontePesquisa;
                fontePesquisa = POST(fontePesquisa);
                count++;
                fonteEncontrada = 0;
            }
        }
    }
}

void buscarSemAspas(Palavra pesquisa, Palavra W, int numPalavras){
    ListaF fontes, auxF, fontePesquisa, antFontePesquisa;
    int fonteEncontrada = 0, count;
    if(numPalavras == 1){
        auxF = FONTE(W);
        alocarFonte(&fontes,-999,CONTEUDO(auxF));
        FONTE(pesquisa) = fontes;
        for(fontePesquisa = FONTE(pesquisa),auxF = POST(auxF);auxF != NULL;fontePesquisa = POST(fontePesquisa),auxF = POST(auxF)){
            alocarFonte(&fontes,-999,CONTEUDO(auxF));
            POST(fontePesquisa) = fontes;
        }
    }
    else {
        for(count = 0,fontePesquisa = FONTE(pesquisa);fontePesquisa != NULL;){
            for(auxF = FONTE(W);auxF != NULL; auxF = POST(auxF))
                if(strcmp(CONTEUDO(fontePesquisa),CONTEUDO(auxF)) == 0){
                    fonteEncontrada = 1;
                    break;
                }
            if(fonteEncontrada == 0 && count == 0){
                FONTE(pesquisa) = POST(fontePesquisa);
                free(fontePesquisa);
                fontePesquisa = FONTE(pesquisa);
                antFontePesquisa = FONTE(pesquisa);
            }
            else if(fonteEncontrada == 0){
                POST(antFontePesquisa) = POST(fontePesquisa);
                free(fontePesquisa);
                fontePesquisa = POST(antFontePesquisa);
                count++;
            }
            else{
                antFontePesquisa = fontePesquisa;
                fontePesquisa = POST(fontePesquisa);
                count++;
                fonteEncontrada = 0;
            }
        }
    }
}

void buscarComAspasEnc(BancoPalavras *banco, Palavra pesquisa){
    char termo[50];
    int indice, i, j, numPalavras = 0;
    Palavra W;
    for(j=0,i=1;i<strlen(CONTEUDO(pesquisa));i++){
        if((CONTEUDO(pesquisa))[i] != ' ' && (CONTEUDO(pesquisa))[i] !='\0' && (CONTEUDO(pesquisa))[i] != 34){
            termo[j] = (CONTEUDO(pesquisa))[i];
            j++;
        }
        else{
            termo[j] = '\0';
            j=0;
            numPalavras++;
            indice = calcularIndice(termo,MAX);
            W = buscarPalavra(banco,termo,indice);
            if(W == NULL){
                return;
            }
            else{
                buscarComAspas(pesquisa,W,numPalavras);
            }
        }
    }
}

void buscarSemAspasEnc(BancoPalavras *banco, Palavra pesquisa){
    char termo[50];
    int indice, i, j, numPalavras = 0;
    Palavra W;
    for(j=0,i=0;i<strlen(CONTEUDO(pesquisa))+1;i++){
        if((CONTEUDO(pesquisa))[i] != ' ' && (CONTEUDO(pesquisa))[i] !='\0'){
                termo[j] = (CONTEUDO(pesquisa))[i];
                j++;
        }
        else{
            termo[j] = '\0';
            j=0;
            numPalavras++;
            indice = calcularIndice(termo,MAX);
            W = buscarPalavra(banco,termo,indice);
            if(W == NULL)
                return;
            else{
                buscarSemAspas(pesquisa,W,numPalavras);
            }
        }
    }
}

void buscarEncadeado(BancoPalavras *banco,ListaP listaBusca){
    Palavra W = PALAVRAS(listaBusca);
    if(QUANTIDADE(listaBusca) == 0){
        printf("Vazio\n");
        return;
    }
    for(;W != NULL;W = POST(W)){
        if((CONTEUDO(W))[0] == 34)
            buscarComAspasEnc(banco,W);
        else{
            buscarSemAspasEnc(banco,W);
        }
    }
}

void buscarComAspasLinDup(BancoPalavrasLinear *bancoLD, Palavra pesquisa,char tipoHash){
    char termo[50];
    int indice, i, j, numPalavras = 0;
    Palavra W;
    for(j=0,i=1;i<strlen(CONTEUDO(pesquisa))+1;i++){
        if((CONTEUDO(pesquisa))[i] != ' ' && (CONTEUDO(pesquisa))[i] !='\0' && (CONTEUDO(pesquisa))[i] != 34){
                termo[j] = (CONTEUDO(pesquisa))[i];
                j++;
        }
        else{
            termo[j] = '\0';
            j=0;
            numPalavras++;
            indice = calcularIndice(termo,MAXLINEAR);
            if(tipoHash == 'l'){
                indice = posicaoPalavraLinear(bancoLD,termo,indice);
                W = (LISTA(bancoLD))[indice];
            }
            if(tipoHash == 'r'){
                indice = posicaoPalavraDuplo(bancoLD,termo,indice);
                W = (LISTA(bancoLD))[indice];
            }
            if(W == NULL){
                return;
            }
            else{
                buscarComAspas(pesquisa,W,numPalavras);
            }
        }
    }
}

void buscarSemAspasLinDup(BancoPalavrasLinear *bancoLD, Palavra pesquisa,char tipoHash){
    char termo[50];
    int indice, i, j, numPalavras = 0;
    Palavra W;
    for(j=0,i=0;i<strlen(CONTEUDO(pesquisa))+1;i++){
        if((CONTEUDO(pesquisa))[i] != ' ' && (CONTEUDO(pesquisa))[i] !='\0'){
                termo[j] = (CONTEUDO(pesquisa))[i];
                j++;
        }
        else{
            termo[j] = '\0';
            j=0;
            numPalavras++;
            indice = calcularIndice(termo,MAXLINEAR);
            if(tipoHash == 'l'){
                indice = posicaoPalavraLinear(bancoLD,termo,indice);
                W = (LISTA(bancoLD))[indice];
            }
            if(tipoHash == 'r'){
                indice = posicaoPalavraDuplo(bancoLD,termo,indice);
                W = (LISTA(bancoLD))[indice];
            }
            if(W == NULL){
                return;
            }
            else{
                buscarSemAspas(pesquisa,W,numPalavras);
            }
        }
    }
}

void buscarLinearDuplo(BancoPalavrasLinear *bancoLD,ListaP listaBusca, char tipoHash){
    Palavra W = PALAVRAS(listaBusca);
    if(QUANTIDADE(listaBusca) == 0){
        printf("Vazio\n");
        return;
    }
    for(;W != NULL;W = POST(W)){
        if((CONTEUDO(W))[0] == 34)
            buscarComAspasLinDup(bancoLD,W,tipoHash);
        else{
            buscarSemAspasLinDup(bancoLD,W,tipoHash);
        }
    }
}