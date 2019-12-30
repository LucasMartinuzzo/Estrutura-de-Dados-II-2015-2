#include <stdio.h>
#include <stdlib.h>
#include "tads.h"
#include "beamSearch.h"
#include "branchBound.h"

int inserirOrdenado (TriplaP *branch, TriplaP *p_T, int n){
    int i;
    TriplaP auxT, T = *p_T;
    for(i=0;i<n && branch[i] != NULL;i++){
        auxT = branch[i];
        if(LB(T) <= LB(auxT)){
            if(LB(T) == LB(auxT) && UB(T) > UB(auxT))
                continue;
            branch[i] = T;
            T = auxT;
        }
    }
    branch[i] = T;
    return 2;
}
int escolherMelhorBranch(TriplaP *p_FinalT, TriplaP* branch, int n){
    int i;
    TriplaP auxT, T, finalT = *p_FinalT;
    T = branch[0];
    for(i=1;i<n && branch[i] !=NULL;i++){
        auxT = branch[i];
        liberarTripla(&auxT);
    }
    if(MULTA(finalT) > MULTA(T)){
        liberarTripla(&finalT);
        *p_FinalT = T;
        return 2;
     }
    else{
        liberarTripla(&T);
        return 3;
    }
    return 1;
}
int concatenarPercurso (TriplaP *p_T, int **matrizJobs){
    TriplaP T = *p_T;
    int j;
    for(j=0;j<TOTAL(T);j++){
        if(NPROC(T)[j] != -1){
            inserirJob(&T,matrizJobs,j);
        }
    }
    return 1;
}

int branchRecursiva(TriplaP *p_FinalT, int **matrizJobs, TriplaP* branch, int n){
    TriplaP filhoT, T = branch[0], finalT;
    int i, j, k, tamAtual = n, tamFilho = n-1;
    if(NUMPROC(T) == TOTAL(T)){
        escolherMelhorBranch(p_FinalT, branch, n);
        free(branch);
        branch = NULL;
        return 2;
    }
    finalT = *p_FinalT;
    for(i=0;i<tamAtual;i++){
        finalT = *p_FinalT;
        T = branch[i];
        if(LB(T) >= MULTA(finalT)){
            liberarTripla(&T);
            branch[i] = NULL;
        }else if(LB(T) == UB(T)){
            concatenarPercurso(&T,matrizJobs);
            liberarTripla(&finalT);
            *p_FinalT = T;
        }else {
            TriplaP *branch2 = (TriplaP*)malloc(tamFilho*sizeof(Tripla));
            if(branch2 == NULL) return -1;
            for(j=0,k=0;j<tamFilho;k++){
                branch2[j] = NULL;
                if(NPROC(T)[k] != -1){
                    alocarTriplaFonte(&filhoT,T,matrizJobs,k);
                    if(j == 0)
                        branch2[j] = filhoT;
                    else
                        inserirOrdenado(branch2,&filhoT,tamFilho);
                    j++;
                }
            }
            liberarTripla(&T);
            branch[i] = NULL;
            if(branchRecursiva(p_FinalT,matrizJobs,branch2,tamFilho) == -1) return -1;
            free(branch2);
            branch2 = NULL;
        }
    }
    return 1;
}

int branchBound(TriplaP *p_T, int **matrizJobs, int nJobs){
    TriplaP T, *branch = (TriplaP*)malloc(nJobs*sizeof(Tripla));
    if(branch == NULL) return -1;
    int i;
    for(i=0;i<nJobs;i++){
        branch[i] = NULL;
        alocarTriplaVazia(&T,nJobs);
        inserirJob(&T,matrizJobs,i);
        if(i==0)
            branch[i] = T;
        else
            inserirOrdenado(branch, &T, nJobs);
    }
    if(branchRecursiva(p_T,matrizJobs,branch,nJobs) == -1) return -1;
    if(nJobs > 1)
        free(branch);
    branch = NULL;
    return 1;
}