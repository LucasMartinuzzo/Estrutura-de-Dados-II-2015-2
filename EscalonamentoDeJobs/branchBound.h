#ifndef BRANCHBOUND_H
#define	BRANCHBOUND_H

#include <stdio.h>
#include <stdlib.h>
#include "tads.h"
#include "beamSearch.h"

int inserirOrdenado (TriplaP*, TriplaP*, int);
int escolherMelhorBranch(TriplaP*, TriplaP*, int);
int concatenarPercurso (TriplaP*, int**);
int branchRecursiva(TriplaP*, int**, TriplaP*, int);
int branchBound(TriplaP*, int**, int);

#endif	/* BRANCHBOUND_H */

