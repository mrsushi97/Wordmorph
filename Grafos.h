#ifndef _GRAFOS_H
#define _GRAFOS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ficheiros.h"
#include "defs.h"
#include "LinkedList.h"

typedef struct graph Graph;

void printGraph(Graph* );
Graph *GRAPHinit(int);
Edge *CriaEdge(int v,int w);
void GRAPHinsertE(Graph *, int, int,int);
void freeStuff(Graph *);
Graph **CriaGrafos( char*, char***, int, int*,int*);
void destroyEdge(Item);

#endif
