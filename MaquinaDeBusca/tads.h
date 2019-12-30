#ifndef TADS_H
#define	TADS_H

#define POST(L) ((L)->posterior)
#define CONTEUDO(L) ((L)->conteudo)
#define POSICOES(L) ((L)->posicoes)
#define QUANTIDADE(L) ((L)->quantidade)
#define PALAVRAS(L) ((L)->palavras)
#define FONTE(L) ((L)->fonte)

typedef struct celula Celula, *Posicoes;
struct celula{
    int conteudo;
    Posicoes posterior;
};

typedef struct listaF mListaF, *ListaF;
struct listaF {
    char* conteudo;
    Posicoes posicoes;
    ListaF posterior;
};

typedef struct palavra mPalavra, *Palavra;
struct palavra{
    char* conteudo;
    ListaF fonte;
    Palavra posterior;
};

typedef struct listaP mListaP, *ListaP;
struct listaP {
    int quantidade;
    Palavra palavras;
};

void inicializarPosicao();

void inicializarPalavra();

void inicializarLista();

void inicializarFonte();

int alocarPosicao();

int alocarPalavra();

int alocarLista();

int alocarFonte();

#endif	/* TADS_H */