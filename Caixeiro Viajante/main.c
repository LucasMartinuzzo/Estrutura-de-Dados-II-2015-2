#include <stdio.h>
#include <stdlib.h>
#include "exato.h"
#include "nn2opt.h"
#include "convexHull.h"

typedef enum {EXATO = 1, NN = 2, OPT = 3, HULL =4} opcao;

int opcaoMenu (char *string){
    if (strcmp(string,"exato") == 0)
        return 1;
    else if(strcmp(string,"nn") == 0)
        return 2;
    else if(strcmp(string,"opt") == 0)
        return 3;
    else if(strcmp(string,"hull") == 0)
        return 4;
    else
        return 0;
}

int exato (int nCidades){
    if(nCidades >= 15){
        printf("*\n");
        exit(1);
    }
    int **matrizDistancias = criarMatrizDistancias(nCidades);
    int *percursoAtual = criarPercursoInicial(nCidades);
    int *menorPercurso = criarPercursoInicial(nCidades);
    int menorDistancia = calcularDistancia(nCidades, matrizDistancias,menorPercurso);
    metodoExato(nCidades, matrizDistancias, &menorDistancia, menorPercurso, percursoAtual, 1, nCidades -1);
    imprimirResultado (nCidades, menorDistancia, menorPercurso);
    free(matrizDistancias);
    free(percursoAtual);
    free(menorPercurso);
    return (EXIT_SUCCESS);
}

int nn (int nCidades){
    int **matrizDistancias = criarMatrizDistancias(nCidades);
    int *percurso = inicializarPercurso(nCidades);
    int distancia;
    vizinhoMaisProximo(nCidades, matrizDistancias, percurso);
    distancia = calcularDistancia(nCidades, matrizDistancias, percurso);
    imprimirResultado (nCidades, distancia, percurso);
    free(matrizDistancias);
    free(percurso);
    return (EXIT_SUCCESS);
}
int opt(int nCidades){
    int **matrizDistancias = criarMatrizDistancias(nCidades);
    int *percurso = inicializarPercurso(nCidades);
    int distancia;
    vizinhoMaisProximo(nCidades, matrizDistancias, percurso);
    distancia = calcularDistancia(nCidades, matrizDistancias, percurso);
    opt2(nCidades, matrizDistancias, percurso, &distancia);
    imprimirResultado (nCidades, distancia, percurso);
    free(matrizDistancias);
    free(percurso);
    return (EXIT_SUCCESS);
}

int convexHull(int nCidades){
    Coordenadas *cidades = criarVetorCoordenadas(nCidades);
    ordenacao (nCidades, cidades);
    Coordenadas *envoltorioSaida = (Coordenadas*)malloc((nCidades+1)*sizeof(Coordenadas));
    if(!envoltorioSaida)
        exit(1);
    int tamEnvoltorio;
    gerarEnvoltorio(nCidades,cidades, envoltorioSaida, &tamEnvoltorio);
    definirPercurso (nCidades, cidades, &tamEnvoltorio, envoltorioSaida);
    Coordenadas *percurso = reordenar(nCidades,envoltorioSaida);
    imprimirResultadoCH (nCidades,percurso);
    free(cidades);
    //free(percurso);
    return (EXIT_SUCCESS);    
}
int main(int argc, char** argv) {
    int nCidades = atoi(argv[1]);
    int opcao = opcaoMenu(argv[2]);
    switch(opcao){
        case EXATO:
            exato(nCidades);
            break;
        case NN:
            nn(nCidades);
            break;
        case OPT:
            opt(nCidades);
            break;
        case HULL:
            convexHull(nCidades);
            break;
        default:
            return 0;
    }
    return (EXIT_SUCCESS);
}

