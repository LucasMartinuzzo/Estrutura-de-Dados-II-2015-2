#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"
#include "linear.h"
#include "rehash.h"
#include "arquivos.h"
#include "buscas.h"

typedef enum {INDEX = 1, BUSCA = 2} opcao;

int opcaoMenu (char *string){
    if (strcmp(string,"-i") == 0)
        return 1;
    else if(strcmp(string,"-b") == 0)
        return 2;
    else
        return 0;
}

void indexEncadeado(char *entradaDocs, char *indiceGerado){
    BancoPalavras *banco;
    banco = criaBanco();
    carregarListaArquivosEnc(banco,entradaDocs);
    salvarIndexEnc(banco,indiceGerado);
    liberarTudo(banco);
}

void indexLinear(char *entradaDocs, char *indiceGerado){
    BancoPalavrasLinear *bancoL;
    bancoL = criaBancoLinear();
    carregarListaArquivosLin(bancoL,entradaDocs);
    salvarIndexLinDup(bancoL,indiceGerado);
    liberarTudoLinear(bancoL);
}

void indexRehash(char *entradaDocs, char *indiceGerado){
    BancoPalavrasLinear *bancoR;
    bancoR = criaBancoLinear();
    carregarListaArquivosDup(bancoR,entradaDocs);
    salvarIndexLinDup(bancoR,indiceGerado);
    liberarTudoLinear(bancoR);
}

void buscaEncadeado(char *indice, char *arquivoBuscas){
    BancoPalavras *banco;
    mListaP *listaBusca;
    banco = criaBanco();
    listaBusca = criaLista();
    carregarIndexEnc(banco,indice);
    carregarListaBusca(listaBusca,arquivoBuscas);
    buscarEncadeado(banco,listaBusca);
    imprimirListaBusca(listaBusca);
    liberarTudo(banco);
    liberarListaBusca(listaBusca);
}

void buscaLinear(char *indice, char *arquivoBuscas){
    BancoPalavrasLinear *bancoL;
    mListaP *listaBusca;
    bancoL = criaBancoLinear();
    listaBusca = criaLista();
    carregarIndexLinDup(bancoL,indice);
    carregarListaBusca(listaBusca,arquivoBuscas);
    buscarLinearDuplo(bancoL,listaBusca,'l');
    imprimirListaBusca(listaBusca);
    liberarTudoLinear(bancoL);
    liberarListaBusca(listaBusca);
}

void buscaRehash(char *indice, char *arquivoBuscas){
    BancoPalavrasLinear *bancoR;
    mListaP *listaBusca;
    bancoR = criaBancoLinear();
    listaBusca = criaLista();
    carregarIndexLinDup(bancoR,indice);
    carregarListaBusca(listaBusca,arquivoBuscas);
    buscarLinearDuplo(bancoR,listaBusca,'r');
    imprimirListaBusca(listaBusca);
    liberarTudoLinear(bancoR);
    liberarListaBusca(listaBusca);
}

void opcaoIndex(char tipoModelo, char *entradaDocs, char *indiceGerado){
    switch(tipoModelo){
        case 'E':
            indexEncadeado(entradaDocs, indiceGerado);
            break;
        case 'L':
            indexLinear(entradaDocs, indiceGerado);
            break;
        case 'R':
            indexRehash(entradaDocs, indiceGerado);
            break;
        default:
            return;
    }
    return;
}

void opcaoBusca (char tipoModelo, char *indice, char *arquivoBuscas){
    switch(tipoModelo){
        case 'E':
            buscaEncadeado(indice, arquivoBuscas);
            break;
        case 'L':
            buscaLinear(indice, arquivoBuscas);
            break;
        case 'R':
            buscaRehash(indice, arquivoBuscas);
            break;
        default:
            return;
    }
    return;
}

int main(int argc, char** argv) {
    int opcao = opcaoMenu(argv[1]);
    switch(opcao){
        case INDEX:
            opcaoIndex(argv[2][0],argv[3], argv[4]);
            break;
        case BUSCA:
            opcaoBusca (argv[2][0],argv[3],argv[4]);
            break;
        default:
            return 0;
    }
    return (EXIT_SUCCESS);
}

