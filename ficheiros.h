#ifndef _FICHEIROS_H
#define _FICHEIROS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *LePalavra ( FILE * f );
FILE *AbreFicheiro ( char *nome, char *mode );
int charcmp(char*, char*, int);
void Readnummax(FILE*, int*);

#endif
