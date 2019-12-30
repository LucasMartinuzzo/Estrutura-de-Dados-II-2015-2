#include <stdio.h>
#include <stdlib.h>
#include "tads.h"

int** criarMatrizJobs (int nJobs){
    int **jobs = (int**)malloc(nJobs*sizeof(int*));
    if(!jobs)
        exit(1);    
    int i, j;
    for (i=0; i<nJobs; i++){
        jobs[i] = (int*)malloc(3*sizeof(int));
        if(!jobs[i])
            exit(1);
        for(j=0; j<3; j++){
            scanf(" %d",&jobs[i][j]);
        }
    }
    return jobs;
}

int liberarMatrizJobs (int **matrizJobs, int nJobs){
    int i;
    for(i=0;i<nJobs;i++)
        free(matrizJobs[i]);
    free(matrizJobs);
    matrizJobs = NULL;
    return 0;
}

int alocarTriplaVazia(TriplaP *p_T, int nJobs){
    TriplaP T = (TriplaP)malloc(sizeof(Tripla));
    if(T == NULL) return -1;
    PROC(T) = (int*)malloc(nJobs*sizeof(int));
    NPROC(T) = (int*)malloc(nJobs*sizeof(int));
    if(PROC(T) == NULL || NPROC(T) == NULL) return -2;
    int i;
    for(i = 0;i<nJobs;i++){
        PROC(T)[i] = -1;
        NPROC(T)[i] = i;
    }
    NUMPROC(T) = 0;
    TOTAL(T) = nJobs;
    TEMPO(T) = 0;
    MULTA(T) = 0;
    LB(T) = 0;
    UB(T) = 0;
    *p_T = T;
    return 1;
}

int liberarTripla(TriplaP *p_T){
    free(PROC(*p_T));
    free(NPROC(*p_T));
    free(*p_T);
    *p_T = NULL;
    return 0;
}

int inserirJob(TriplaP *p_T, int **matrizJobs, int job){
    TriplaP T = *p_T;
    if(T == NULL) return -1;
    if(TOTAL(T) == NUMPROC(T)){
        return 0;
    }
    int i;
    int tempoProc = matrizJobs[job][0];
    int lim = matrizJobs[job][1];
    int multa = matrizJobs[job][2];
    for(i=0;i<NUMPROC(T);i++){
        if(PROC(T)[i] == job){
            return -1;
        }
    }
    PROC(T)[NUMPROC(T)] = job;
    NPROC(T)[job] = -1;
    NUMPROC(T)++;
    TEMPO(T)+=tempoProc;
    if(lim <TEMPO(T))
        MULTA(T)+= multa;
    LB(T) = MULTA(T);
    UB(T) = MULTA(T);
    for(i=0;i<TOTAL(T);i++){
        if(NPROC(T)[i] != -1){
            tempoProc = matrizJobs[i][0];
            lim = matrizJobs[i][1];
            multa = matrizJobs[i][2];
            if(TEMPO(T) + tempoProc > lim)
                LB(T)+= multa;
            UB(T)+=multa;
        }
    }
    return 1;
}

int alocarTriplaFonte(TriplaP *p_T, TriplaP pai, int **matrizJobs, int job){
    TriplaP T = (TriplaP)malloc(sizeof(Tripla));
    if(T == NULL) return -1;
    PROC(T) = (int*)malloc(TOTAL(pai)*sizeof(int));
    NPROC(T) = (int*)malloc(TOTAL(pai)*sizeof(int));
    if(PROC(T) == NULL || NPROC(T) == NULL) return -2;
    int i;
    for(i=0;i<TOTAL(pai);i++){
        PROC(T)[i] = PROC(pai)[i];
        NPROC(T)[i] = NPROC(pai)[i];
    }
    NUMPROC(T) = NUMPROC(pai);
    TOTAL(T) = TOTAL(pai);
    TEMPO(T) = TEMPO(pai);
    MULTA(T) = MULTA(pai);
    if(inserirJob(&T,matrizJobs, job) == 1){
        *p_T = T;
        return 1;
    }
    else
        return -3;
}