#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum entrada {ALEATORIO = 1, CRESCENTE, DECRESCENTE};

int opcoes (char opcao){
    if(opcao == 'a')
        return ALEATORIO;
    if(opcao == 'c')
        return CRESCENTE;
    if(opcao == 'd')
        return DECRESCENTE;
    return 0;
}
void geradorAleatorio (int n){
    int i;
    srand(time(NULL));
    for(i=0;i<n;i++){
        printf("%d\n",rand() % 1000001);
    }
}

void geradorCrescente (int n){
    int i, j;
    srand(time(NULL));
    for(j=0,i=0;i<n;i++){
        if( j > 1000000)
            j = 1000000;
        printf("%d\n",j);
        if(rand()%7 != 0)
            j+= (rand() % 3);
    }
}

void geradorDecrescente (int n){
    int i, j;
    srand(time(NULL));
    for(j=n,i=0;i<n;i++){
        printf("%d\n",j);
        if(rand()%7 != 0)
            j--;
    }
}


int main(int argc, char** argv) {
    int n = atoi(argv[2]);
    int opcao = opcoes(argv[1][1]);
    switch (opcao){
        case ALEATORIO:
            geradorAleatorio(n);
            break;
        case CRESCENTE:
            geradorCrescente(n);
            break;
        case DECRESCENTE:
            geradorDecrescente(n);
            break;
        default:
            break;
    }
    return (EXIT_SUCCESS);
}

