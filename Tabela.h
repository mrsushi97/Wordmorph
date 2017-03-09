#ifndef _TABELA_H
#define _TABELA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ficheiros.h"

void AlocaTabelaPalavras ( char *ficheiro, int *lenght_vector, char**** Tabelapalavras, int *max_lenght_palavra );
void PreencheTabelaPalavras ( char *ficheiro, char*** Tabelapalavras, int* lenght_vector, int max_lenght_palavra,int* );
void ordenatabela( char ***Tabelapalavras, int max_lenght_palavra, int *lenght_vector,int*);
int switcheroo(const void *a, const void *b);
void Libertamemoria(char*** Tabelapalavras,int max_lenght_palavra,int* lenght_vector);
#endif
