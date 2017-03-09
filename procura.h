#ifndef _PROCURA_H
#define _PROCURA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "Grafos.h"
#include "defs.h"

typedef struct heap heap_;


void printPath(int* , int,char**,FILE*);
heap_* novaheap(int);
void Insert(heap_* , int);
void Heapify(heap_ *);
void FixDown(heap_* , int );
void FixUp(heap_*, int);
int isEmpty(heap_*);
int Minvertice(heap_*);
void update_dist(heap_*, int, int);
bool estanaheap(heap_*, int);
void getpath(Graph*, int, int, char**,FILE*,int);
int procurabinaria(char*, int, char**);
void LePal(char* , Graph **, char ***, int*);

#endif
