#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ficheiros.h"
#include "Tabela.h"

/******************************************************************************
 * AlocaTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void AlocaTabelaPalavras ( char *ficheiro, int *lenght_vector, char**** Tabelapalavras, int *max_lenght_palavra )
{
  FILE *f;
  char *palavra;
  f = AbreFicheiro ( ficheiro, "r" );

  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    if(strlen(palavra) > *max_lenght_palavra)
      *max_lenght_palavra = strlen(palavra);
    lenght_vector[strlen(palavra)-1]++;
  }

  fclose(f);

  *Tabelapalavras = (char ***) malloc(*max_lenght_palavra*sizeof(char**));
  if ( *Tabelapalavras == NULL ) {
    exit (0);
  }
  return;
}
/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras ( char *ficheiro, char*** Tabelapalavras, int* lenght_vector, int max_lenght_palavra, int* num_letras_max )
{
  FILE *f;
  int n;
  char *palavra;
  int pos_vector[100] = {0};

  f = AbreFicheiro ( ficheiro, "r" );
  for(n=0; n < max_lenght_palavra; n++){
    if(num_letras_max[n] > 0){
      Tabelapalavras[n] = (char **) malloc((lenght_vector[n]*sizeof(char*)));
      if ( Tabelapalavras[n] == NULL ) {
        exit (0);
      }
    }
    else
      Tabelapalavras[n] = NULL;
  }

  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    if(num_letras_max[strlen(palavra)-1] > 0){
      Tabelapalavras[strlen(palavra)-1][pos_vector[strlen(palavra)-1]] = (char *) malloc((strlen(palavra)+1)*sizeof(char));
      if ( Tabelapalavras[strlen(palavra)-1][pos_vector[strlen(palavra)-1]] == NULL ) {
        exit (0);
      }
      strcpy ( Tabelapalavras[strlen(palavra)-1][pos_vector[strlen(palavra)-1]], palavra );
      pos_vector[strlen(palavra)-1]++;
    }
  }

  fclose ( f );
  return;
}

/******************************************************************************
 * Libertamemoria
 *
 * Arguments: Tabelapalavras - pointer to string matrix
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
void Libertamemoria(char*** Tabelapalavras,int max_lenght_palavra,int* lenght_vector)
{
  int i,j;
  for(i=0;i<max_lenght_palavra;i++){
    if(Tabelapalavras[i] != NULL)
      for(j=0;j<lenght_vector[i];j++){

          free(Tabelapalavras[i][j]);
        }
    free(Tabelapalavras[i]);
  }
    free(Tabelapalavras);

}

/******************************************************************************
 * switcheroo
 *
 * Basic function to compare two strings of type
 *
 *****************************************************************************/
int switcheroo(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

/******************************************************************************
 * ordenatabela
 *
 * Arguments: Tabelapalavras - pointer to string matrix
 *            max_lenght_palavra - maximum string lenght
 *			  lenght_vector - vector of number of words per string lenght
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
void ordenatabela( char ***Tabelapalavras, int max_lenght_palavra, int *lenght_vector,int* num_letras_max){
    int i;
    for(i=0;i<max_lenght_palavra;i++){
      if(num_letras_max[i] > 0)
        qsort(Tabelapalavras[i],lenght_vector[i], sizeof(char *), switcheroo);

    }
}
