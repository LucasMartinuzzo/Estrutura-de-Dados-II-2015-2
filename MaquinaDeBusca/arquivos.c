#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tads.h"
#include "encadeamento.h"
#include "linear.h"
#include "arquivos.h"
#include "rehash.h"
#include "buscas.h"

char *retirarAcentos (char* string, char verificador){
    char palavra [TAM_TERMO];
    int i,k = 0;
    for(i=0;i<strlen(string);i++){
        if((string[i] >= 97 && string[i] <= 122) || (string[i] >= 48 && string[i] <= 57)){
            palavra[k] = string[i];
            k++;
            continue;
        }
        else if (string[i] >= 65 && string[i] <= 90){
            palavra[k] = string[i] + 32;
            k++;
            continue;
        }
        else if(verificador == 'b' && (string[i] == 34 || string[i] == 32)){
            palavra[k] = string[i];
            k++;
            continue;
        }
    }
    palavra[k] = '\0';
    if(strlen(palavra) == 0)
        return NULL;
    char *p = (char*)malloc(sizeof(char)*(strlen(palavra)+1));
    if(p == NULL)
        return NULL;
    strcpy(p,palavra);
    return p;
}

int carregarArquivoEnc(BancoPalavras *banco, char *arquivo){
    FILE *fp;
    int pos = 0;
    char *aux = NULL, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while( !feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = retirarAcentos(palavra,'c');
        if(aux == NULL){
            continue;
        }
        inserirPalavra(banco,aux,pos,arquivo);
        pos++;
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo '%s'.\n",arquivo);
        return -2;
    }
    printf("Arquivo carregado com sucesso.\n");
    return 1;
}

int carregarListaArquivosEnc (BancoPalavras *banco, char *arquivo){
    FILE *fp;
    char *aux, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = (char *)malloc ((sizeof (char))*(strlen (palavra) + 1));
        if(aux == NULL){
            printf("Nao foi possivel alocar memoria 1.\n");
            return -3;
        }
        strcpy (aux, palavra);
        carregarArquivoEnc(banco,aux);
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivos carregados com sucesso.\n");
    return 1;
}

int carregarArquivoLin(BancoPalavrasLinear *banco, char *arquivo){
    FILE *fp;
    int pos = 0;
    char *aux, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while( !feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = retirarAcentos(palavra,'c');
        if(aux == NULL){
            continue;
        }
        inserirPalavraLinear(banco,aux,pos,arquivo);
        pos++;
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo '%s'.\n",arquivo);
        return -2;
    }
    printf("Arquivo carregado com sucesso.\n");
    return 1;
}

int carregarListaArquivosLin (BancoPalavrasLinear *banco, char *arquivo){
    FILE *fp;
    char *aux, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = (char *)malloc ((sizeof (char))*(strlen (palavra) + 1));
        if(aux == NULL){
            printf("Nao foi possivel alocar memoria2.\n");
            return -3;
        }
        strcpy (aux, palavra);
        carregarArquivoLin(banco,aux);
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivos carregados com sucesso.\n");
    return 1;
}

int carregarArquivoDup(BancoPalavrasLinear *banco, char *arquivo){
    FILE *fp;
    int pos = 0;
    char *aux, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while( !feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = retirarAcentos(palavra,'c');
        if(aux == NULL){
            continue;
        }
        inserirPalavraDuplo(banco,aux,pos,arquivo);
        pos++;
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo '%s'.\n",arquivo);
        return -2;
    }
    printf("Arquivo carregado com sucesso.\n");
    return 1;
}

int carregarListaArquivosDup (BancoPalavrasLinear *banco, char *arquivo){
    FILE *fp;
    char *aux, palavra[TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%s\n",palavra);
        aux = (char *)malloc ((sizeof (char))*(strlen (palavra) + 1));
        if(aux == NULL){
            printf("Nao foi possivel alocar memoria.\n");
            return -3;
        }
        strcpy (aux, palavra);
        carregarArquivoDup(banco,aux);
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivos carregados com sucesso.\n");
    return 1;
}

int carregarListaBusca(ListaP listaBusca,char *arquivo){
    FILE *fp;
    int c = 0;
    char *aux, palavra[TAM_TERMO];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo de busca. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%[^\n]\n",palavra);
        aux = retirarAcentos(palavra,'b');
        if(aux == NULL){
            continue;
        }
        inserirPalavrasBusca(listaBusca,aux,c);
        QUANTIDADE(listaBusca)++;
        c++;
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivos carregados com sucesso.\n");
    return 1;
}

int salvarIndexLinDup(BancoPalavrasLinear *bancoLD, char *arquivo){
    FILE *fp;
    int i;
    Palavra W;
    ListaF F;
    Posicoes P;
    if((fp = fopen(arquivo,"w")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    if(QUANTIDADE(bancoLD) == 0)
        return  0;
    for(i=0;i<MAXLINEAR;i++){
        W = (LISTA(bancoLD))[i];
        if(W != NULL){
            fprintf(fp,"%d",i);
            fprintf(fp," %s",CONTEUDO(W));
            for(F = FONTE(W); F!=NULL; F=POST(F)){
                fprintf(fp," %s",CONTEUDO(F));
                for(P = POSICOES(F); P!=NULL; P=POST(P)){
                    fprintf(fp," %d",CONTEUDO(P));
                }
                fprintf(fp," %d",-99);
            }
            fprintf(fp," %d\n",-999);
        }
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivo de indexacao criado com sucesso.\n");
    return 1;
}

int salvarIndexEnc(BancoPalavras *banco, char *arquivo){
    FILE *fp;
    int i;
    ListaP L;
    Palavra W;
    ListaF F;
    Posicoes P;
    if((fp = fopen(arquivo,"w")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    for(i=0;i<MAX;i++){
        L = LISTA(banco)[i];
        if(QUANTIDADE(L) != 0){
            fprintf(fp,"%d",i);
            for(W = PALAVRAS(L); W!=NULL; W=POST(W)){
                fprintf(fp," %s",CONTEUDO(W));
                for(F = FONTE(W); F!=NULL; F=POST(F)){
                    fprintf(fp," %s",CONTEUDO(F));
                    for(P = POSICOES(F); P!=NULL; P=POST(P)){
                        fprintf(fp," %d",CONTEUDO(P));
                    }
                    fprintf(fp," %d",-99);
                }
                fprintf(fp," %d",-999);
            }
            fprintf(fp," %d\n", -9999);
        }
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivo de indexacao criado com sucesso.\n");
    return 1;
}

int carregarIndexLinDup(BancoPalavrasLinear *bancoLD, char *arquivo){
    FILE *fp;
    int i, pos, verificadorF, verificadorP;
    Palavra W;
    ListaF F, p_F;
    Posicoes P, p_P;
    char *auxW, *auxF, palavraW [TAM_FILE], palavraF [TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%d ",&i);
        fscanf(fp,"%s\n",palavraW);
        auxW = (char *)malloc ((sizeof (char))*(strlen (palavraW) + 1));
        if(auxW == NULL){
            printf("Nao foi possivel alocar memoria.\n");
            return -3;
        }
        strcpy(auxW,palavraW);
        alocarPalavra(&W,auxW,0," ");
        LISTA(bancoLD)[i] = W;
        verificadorF = 0;
        QUANTIDADE(bancoLD)++;
        while(1){
            fscanf(fp,"%s\n",palavraF);
            if(strcmp(palavraF,"-999") == 0)
                break;
            auxF = (char *)malloc ((sizeof (char))*(strlen (palavraF) + 1));
            if(auxF == NULL){
                printf("Nao foi possivel alocar memoria.\n");
                return -3;
            }
            strcpy (auxF, palavraF);
            alocarFonte(&F,-999,auxF);
            if(verificadorF == 0){
                FONTE(W) = F;
                p_F = F;
            }
            else{
                POST(p_F) = F;
                p_F = F;
            }
            verificadorF = 1;
            verificadorP = 0;
            while(1){
                fscanf(fp," %d\n",&pos);
                if(pos == -99)
                    break;
                alocarPosicao(&P,pos);
                if(verificadorP == 0){
                    POSICOES(p_F) = P;
                    p_P = P;
                }
                else{
                    POST(p_P) = P;
                    p_P = P;
                }
                verificadorP = 1;
            }
        }
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivo de indexacao carregado com sucesso.\n");
    return 1;
}

int carregarIndexEnc(BancoPalavras *banco, char *arquivo){
    FILE *fp;
    int i, pos,verificadorW, verificadorF, verificadorP;
    ListaP L;
    Palavra W,p_W;
    ListaF F, p_F;
    Posicoes P, p_P;
    char *auxW, *auxF, palavraW [TAM_FILE], palavraF [TAM_FILE];
    if((fp = fopen(arquivo,"r")) == NULL){
        printf("Erro na abertura do arquivo. %s\n", arquivo);
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%d ",&i);
        L = LISTA(banco)[i];
        verificadorW = 0;
        while(1){
            fscanf(fp,"%s\n",palavraW);
            if(strcmp(palavraW,"-9999") == 0)
                break;
            auxW = (char *)malloc ((sizeof (char))*(strlen (palavraW) + 1));
            if(auxW == NULL){
                printf("Nao foi possivel alocar memoria.\n");
                return -3;
            }
            strcpy (auxW, palavraW);
            alocarPalavra(&W,auxW,0," ");
            if(verificadorW == 0){
                PALAVRAS(L) = W;
                p_W = W;
            }
            else{
                POST(p_W) = W;
                p_W = W;
            }
            QUANTIDADE(L)++;
            verificadorW = 1;
            verificadorF = 0;
            while(1){
                fscanf(fp,"%s\n",palavraF);
                if(strcmp(palavraF,"-999") == 0)
                    break;
                auxF = (char *)malloc ((sizeof (char))*(strlen (palavraF) + 1));
                if(auxF == NULL){
                    printf("Nao foi possivel alocar memoria.\n");
                    return -3;
                }
                strcpy (auxF, palavraF);
                alocarFonte(&F,-999,auxF);
                if(verificadorF == 0){
                    FONTE(p_W) = F;
                    p_F = F;
                }
                else{
                    POST(p_F) = F;
                    p_F = F;
                }
                verificadorF = 1;
                verificadorP = 0;
                while(1){
                    fscanf(fp," %d\n",&pos);
                    if(pos == -99)
                        break;
                    alocarPosicao(&P,pos);
                    if(verificadorP == 0){
                        POSICOES(p_F) = P;
                        p_P = P;
                    }
                    else{
                        POST(p_P) = P;
                        p_P = P;
                    }
                    verificadorP = 1;
                }
                
            }
            
        }
    }
    if(fclose(fp)){
        printf("Erro no fechamento do arquivo.%s\n", arquivo);
        return -2;
    }
    printf("Arquivo de indexacao carregado com sucesso.\n");
    return 1;
}