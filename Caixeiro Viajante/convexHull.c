#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convexHull.h"
#include "nn2opt.h"

Coordenadas* criarVetorCoordenadas(int nCidades){
    Coordenadas *cidades = (Coordenadas*)malloc((nCidades)*sizeof(Coordenadas));
    if(!cidades)
        exit(1);
    int i;
    for (i=0;i<nCidades;i++){
       cidades[i].cidade = i;
       scanf("%f",&(cidades[i].x));
       scanf("%f",&(cidades[i].y));
    }
    return cidades;
}

void ordenacao (int nCidades, Coordenadas *cidades){
    int i, j;
    Coordenadas temp;
    for(i = 0;i<nCidades -1;i++)
        for(j=1;j<nCidades;j++)
            if (cidades[j].x < cidades[j -1].x){
                temp = cidades[j];
                cidades[j] = cidades[j-1];
                cidades[j-1] = temp;
            } else
                if(cidades[j].x == cidades[j-1].x){
                    if(cidades[j].y < cidades[j-1].y){
                        temp = cidades[j];
                        cidades[j] = cidades[j-1];
                        cidades[j-1] = temp;
                    }
                }
}

float distanciaEuclidiana (Coordenadas cidadeA, Coordenadas cidadeB){
    float dist1 = pow((cidadeB.x - cidadeA.x),2);
    float dist2 = pow((cidadeB.y - cidadeA.y),2);
    return sqrt(dist1 + dist2);
}

float calcularDistanciaEuc (int nCidades, Coordenadas *envoltorio){
    int i;
    float distancia = 0;
    for(i=0;i<nCidades-1;i++)
        distancia+=distanciaEuclidiana(envoltorio[i],envoltorio[i+1]);
    distancia+=distanciaEuclidiana(envoltorio[i],envoltorio[0]);
    return distancia;
}

float examinarRotacao (Coordenadas cidadeA, Coordenadas cidadeB, Coordenadas cidadeC){
    return (cidadeB.x-cidadeA.x)*(cidadeC.y - cidadeA.y) - (cidadeB.y - cidadeA.y)*(cidadeC.x - cidadeA.x);
}

void gerarEnvoltorio(int nCidades, Coordenadas *cidades, Coordenadas *envoltorioSaida, int *tamEnvoltorio){
    int i, j=0, k;
    for(i=0;i<nCidades;i++){
        while(j>=2 && examinarRotacao(envoltorioSaida[j-2], envoltorioSaida[j-1], cidades[i]) <= 0)
            j--;
        envoltorioSaida[j++] = cidades[i];
    }
    for(i=nCidades -2, k=j+1;i>=0;i--){
        while(j >= k && examinarRotacao(envoltorioSaida[j-2],envoltorioSaida[j-1],cidades[i]) <=0)
            j--;
        envoltorioSaida[j++] = cidades[i];
    }
    *tamEnvoltorio = j;
}

void inserirCidade (int *tamPercurso, Coordenadas *percurso, int posicao, Coordenadas *cidade){
    int i = *tamPercurso;
    for(;i>posicao;i--){
        percurso[i] = percurso[i-1];
    }
    percurso[i] = *cidade;
    (*tamPercurso)++;
}

bool verificarCidade (Coordenadas *cidade, int tamEnvoltorio, Coordenadas *envoltorio){
    int i;
    for(i=0;i<tamEnvoltorio;i++)
        if((cidade->cidade) == envoltorio[i].cidade)
            return true;
    return false;
}

int definirPosicaoAuxiliar (int posicao, int tamEnvoltorio, Coordenadas *envoltorio, Coordenadas *cidade){
    int distanciaAntes, distanciaDepois;
    if(posicao ==0){
        distanciaAntes = distanciaEuclidiana(*cidade, envoltorio[posicao]) + 
                     distanciaEuclidiana(*cidade,envoltorio[tamEnvoltorio -2]) - distanciaEuclidiana(envoltorio[posicao],envoltorio[tamEnvoltorio-2]);
        distanciaDepois = distanciaEuclidiana(*cidade, envoltorio[posicao]) + 
                     distanciaEuclidiana(*cidade,envoltorio[posicao +1]) - distanciaEuclidiana(envoltorio[posicao],envoltorio[posicao+1]);
        if(distanciaAntes < distanciaDepois)
            return tamEnvoltorio-1;
        else
            return 1;
    }
    else{
        distanciaAntes = distanciaEuclidiana(*cidade, envoltorio[posicao]) + 
                     distanciaEuclidiana(*cidade,envoltorio[posicao -1]) - distanciaEuclidiana(envoltorio[posicao],envoltorio[posicao-1]);
        distanciaDepois = distanciaEuclidiana(*cidade, envoltorio[posicao]) + 
                     distanciaEuclidiana(*cidade,envoltorio[posicao +1]) - distanciaEuclidiana(envoltorio[posicao],envoltorio[posicao+1]);
        if(distanciaAntes < distanciaDepois)
            return posicao;
        else
            return posicao +1;
    }
}

int definirPosicaoCidade (Coordenadas *cidade, int tamEnvoltorio, Coordenadas *envoltorio){
    float menorDistancia=-1, distancia;
    int posicao, i;
    for(i=0;i<tamEnvoltorio;i++){
        distancia = distanciaEuclidiana(*cidade, envoltorio[i]);
        if(distancia < menorDistancia || menorDistancia== -1){
            menorDistancia = distancia;
            posicao = i;
        }
    }
    posicao = definirPosicaoAuxiliar (posicao, tamEnvoltorio, envoltorio, cidade);
    return posicao;
}

void definirPercurso (int nCidades, Coordenadas *cidades, int *tamEnvoltorio, Coordenadas *envoltorio){
    int i, posicao;
    for(i=0;i<nCidades;i++)
        if(!verificarCidade(&cidades[i],*tamEnvoltorio, envoltorio)){
            posicao = definirPosicaoCidade(&cidades[i], *tamEnvoltorio, envoltorio);
            inserirCidade (tamEnvoltorio, envoltorio, posicao, &cidades[i]);
        }
}

Coordenadas *reordenar (int nCidades, Coordenadas *envoltorio){
    int i=0,j;
    while(envoltorio[i].cidade != 0)
        i++;
    Coordenadas *percurso = (Coordenadas*)malloc(nCidades*sizeof(Coordenadas));
    if(!percurso)
        exit(1);
    for(j=0;i<nCidades;i++,j++)
        percurso[j]=envoltorio[i];
    for(i=0;j<nCidades;j++,i++)
        percurso[j] = envoltorio[i];
    free(envoltorio);
    return percurso;
}

void imprimirResultadoCH (int nCidades, Coordenadas *envoltorio){
    int i;
    for (i=0;i<nCidades;i++)
        printf("%d\n",envoltorio[i].cidade);
    float distancia = calcularDistanciaEuc(nCidades,envoltorio);
    printf("%f\n*\n", distancia);
}
