#ifndef CONVEXHULL_H
#define	CONVEXHULL_H
#include "nn2opt.h"

typedef struct {
    float x;
    float y;
    int cidade;
}Coordenadas;

Coordenadas* criarVetorCoordenadas();
void ordenacao();
float distanciaEuclidiana();
float calcularDistanciaEuc();
float examinarRotacao();
void gerarEnvoltorio();
void inserirCidade ();
bool verificarCidade();
int definirPosicaoAuxiliar();
int definirPosicaoCidade();
void definirPercurso();
Coordenadas *reordenar();
void imprimirResultadoCH();

#endif	/* CONVEXHULL_H */

