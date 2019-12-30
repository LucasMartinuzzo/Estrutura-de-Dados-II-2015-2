#ifndef BEAMSEARCH_H
#define	BEAMSEARCH_H
#define BEAM_WIDTH 7
#include <stdio.h>
#include <stdlib.h>
#include "tads.h"

int escolherMelhores(TriplaP*, TriplaP*, int);
int escolherMelhor(TriplaP*, TriplaP*, int);
int beamRecursiva(TriplaP*, int**, int, TriplaP*, int);
int beamSearch(TriplaP*, int**, int);
int imprimirBeam (int, TriplaP[]);

#endif	/* BEAMSEARCH_H */

