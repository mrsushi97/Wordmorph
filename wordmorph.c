/******************************************************************************
 *
 * File Name: wordmorph.c
 * Authors:    Pedro Távora nº84162 e Luís Ferreira nº84122
 *
 * COMMENTS:    Version with no globals variables
 *		Passing structure for functions
 *		More compact test for EOF
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ficheiros.h"
#include "Tabela.h"
#include "Grafos.h"
#include "procura.h"

int main ( int argc, char **argv )
{

  char*** Tabelapalavras = NULL;
  int lenght_vector[100] = {0};
  int max_lenght_palavra = 0,i;
  int num_letras_max[100] = {0};
  char arg1[100] = "\0";
  char arg2[100] = "\0";
  FILE* f2 = NULL;
  Graph **G = NULL;

  if ( argc < 3 ) {
    exit ( 0 );
  }

  strcpy(arg1,argv[1]);
  if(arg1[strlen(arg1)-4] != '.'  || arg1[strlen(arg1)-3] != 'd' || arg1[strlen(arg1)-2] != 'i' || arg1[strlen(arg1)-1] != 'c')
    exit(0);
  strcpy(arg2,argv[2]);
  if(arg2[strlen(arg2)-4] != '.'  || arg2[strlen(arg2)-3] != 'p' || arg2[strlen(arg2)-2] != 'a' || arg2[strlen(arg2)-1] != 'l')
    exit(0);

  f2 = AbreFicheiro(arg2, "r");
  /*Lê o ficheiro de problemas*/
  Readnummax(f2,num_letras_max);
  fclose(f2);


  AlocaTabelaPalavras ( arg1, lenght_vector,&Tabelapalavras,&max_lenght_palavra);
  PreencheTabelaPalavras ( arg1,Tabelapalavras,lenght_vector,max_lenght_palavra,num_letras_max);
  ordenatabela(Tabelapalavras, max_lenght_palavra, lenght_vector,num_letras_max);
  G = CriaGrafos(arg2, Tabelapalavras, max_lenght_palavra,lenght_vector,num_letras_max);
  LePal(arg2,G,Tabelapalavras,lenght_vector);
  for(i=0; i < max_lenght_palavra;i++)
    freeStuff(G[i]);
  free(G);
  Libertamemoria(Tabelapalavras,max_lenght_palavra,lenght_vector);

  return 0;
}
