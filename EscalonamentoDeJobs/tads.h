#ifndef TADS_H
#define	TADS_H

#include <stdio.h>
#include <stdlib.h>

#define PROC(L) ((L)->processados)
#define NPROC(L) ((L)->naoProcessados)
#define NUMPROC(L) ((L)->numProcessados)
#define TOTAL(L) ((L)->total)
#define TEMPO(L) ((L)->tempoAtual)
#define MULTA(L) ((L)->multaAcumulada)
#define LB(L) ((L)->lowerBound)
#define UB(L) ((L)->upperBound)

typedef struct tripla Tripla, *TriplaP;
struct tripla{
    int* processados;
    int *naoProcessados;
    int numProcessados;
    int total;
    int tempoAtual;
    int multaAcumulada;
    int lowerBound;
    int upperBound;
};

int** criarMatrizJobs (int);
int liberarMatrizJobs (int**, int);
int alocarTriplaVazia(TriplaP*, int);
int liberarTripla(TriplaP*);
int inserirJob(TriplaP*, int**, int);
int alocarTriplaFonte(TriplaP*, TriplaP, int**, int);

#endif	/* TADS_H */

