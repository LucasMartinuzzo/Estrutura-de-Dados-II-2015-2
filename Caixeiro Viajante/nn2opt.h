#ifndef NN2OPT_H
#define	NN2OPT_H

typedef enum {false, true} bool;

int **criarMatrizDistancas();
int calcularDistancia();
void imprimirResultado();
bool cidadeVisitada();
int *inicializarPercurso();
void vizinhoMaisProximo();
void trocar();
void inverter();
void opt2();

#endif	/* NN2OPT_H */

