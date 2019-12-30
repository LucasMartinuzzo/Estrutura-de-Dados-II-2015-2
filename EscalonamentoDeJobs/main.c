#include <stdio.h>
#include <stdlib.h>
#include "tads.h"
#include "beamSearch.h"
#include "branchBound.h"
#include <string.h>

int main(int argc, char** argv) {
    TriplaP T;
    int i;
    int nJobs = atoi(argv[1]);
    int **matrizJobs = criarMatrizJobs(nJobs);
    char *opcao1 = "bs";
    char *opcao2 = "bb";
    if(strcmp(argv[2],opcao1) == 0 || strcmp(argv[2],opcao2) == 0){
        if(beamSearch(&T,matrizJobs,nJobs) == -1) return(EXIT_FAILURE);
        if(strcmp(argv[2],opcao2) == 0 && nJobs > 1){
            if(branchBound(&T,matrizJobs,nJobs) == -1) return (EXIT_FAILURE);
        }
        printf("%d: ",MULTA(T));
        for(i=0;i<nJobs;i++){
            printf("%d ",PROC(T)[i]);
        }
        printf("\n");
        liberarTripla(&T);
    }
    liberarMatrizJobs(matrizJobs, nJobs);
    
    /*imprimir(nJobs,matrizJobs*/
    return (EXIT_SUCCESS);
}

