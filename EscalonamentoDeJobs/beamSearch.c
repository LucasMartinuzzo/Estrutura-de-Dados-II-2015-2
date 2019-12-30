#include <stdio.h>
#include <stdlib.h>
#include "tads.h"
#include "beamSearch.h"

int escolherMelhores(TriplaP *beam, TriplaP *p_T, int n){
    int i;
    TriplaP auxT, T = *p_T;
    for(i=0;i<n && beam[i] != NULL;i++){
        auxT = beam[i];
        if(LB(T) < LB(auxT)){
            beam[i] = T;
            T = auxT;
        }
    }
    if(i<n)
        beam[i] = T;
    else{
        liberarTripla(&T);
        *p_T = NULL;
    }
    return 2;
}

int escolherMelhor(TriplaP *beam, TriplaP *p_T, int n){
    int i;
    TriplaP auxT, T;
    T = beam[0];
    for(i=1;i<n && beam[i] !=NULL;i++){
        auxT = beam[i];
        liberarTripla(&auxT);
    }
    *p_T = T;
    return 1;
}


int beamRecursiva(TriplaP *p_T, int **matrizJobs, int nJobs, TriplaP *beam, int n){
    TriplaP filhoT, T = beam[0];
    int tamBeam = NUMPROC(T);
    int i,j,k;
    if(NUMPROC(T) == TOTAL(T)){
        escolherMelhor(beam, p_T,n);
        free(beam);
        beam = NULL;
        return 2;
    }
    if(tamBeam == 1)
        tamBeam = nJobs;
    else
        tamBeam = n;
    TriplaP *beam2 = (TriplaP*)malloc(n*sizeof(Tripla));
    if(beam2 == NULL) return -1;
    for(i=0;i<n;i++)
        beam2[i] = NULL;
    for(i=0,k=0;i<tamBeam && beam[i] != NULL;i++){
        T = beam[i];
        for(j=0;j<nJobs;j++){
            if(NPROC(T)[j] != -1){
                alocarTriplaFonte(&filhoT,T,matrizJobs,j);
                if(k == 0){
                    beam2[k] = filhoT;
                }
                else{
                    escolherMelhores(beam2,&filhoT,n);
                }
                k++;
            }
        }
        liberarTripla(&T);
    }
    free(beam);
    beam = NULL;
    if(beamRecursiva(p_T, matrizJobs, nJobs, beam2,n) == -1) return -1;
    return 1;
}

int beamSearch(TriplaP *p_T, int **matrizJobs, int nJobs){
    TriplaP *beam = (TriplaP*)malloc(nJobs*sizeof(Tripla));
    if(beam == NULL) return -1;
    TriplaP T;
    int i;
    for(i=0;i<nJobs;i++){
        alocarTriplaVazia(&T,nJobs);
        inserirJob(&T,matrizJobs,i);
        beam[i] = T;
    }
    T = NULL;
    if(beamRecursiva(&T, matrizJobs, nJobs, beam, BEAM_WIDTH) == -1) return -1;
    *p_T = T;
    return 1;
}
/*Função para testes*/
/*
    int imprimirBeam (int nJobs, TriplaP *beam){
    int i, j, n = NUMPROC(beam[0]);
    printf("%d\n",n);
    for(i=0;i<nJobs && beam[i] != NULL;i++){
        printf("%d:\n\tProcessados:",i);
        for(j=0;j<NUMPROC(beam[i]);j++)
            printf(" %d",PROC(beam[i])[j]);
        printf(". Nao processados:");
        for(j=0;j<TOTAL(beam[i]);j++)
            if(NPROC(beam[i])[j] != -1)
                printf(" %d",NPROC(beam[i])[j]);
        printf(".\n\tTempo: %d. Multa: %d.",TEMPO(beam[i]),MULTA(beam[i]));
        printf(" Lower bound: %d. Upper bound: %d.\n",LB(beam[i]),UB(beam[i]));
    }
    printf("FIM!\n");
    return 1;
}
*/