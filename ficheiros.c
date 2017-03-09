#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STR 100

#include "ficheiros.h"

/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns: pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

char *LePalavra ( FILE * f )
{
  static char palavra[MAX_STR];
  /* It is assumed that the words present in the text files do not exceed
     100 characters in length  */
  /* Note that the variable palavra is declared as "static". */
  if ( fscanf ( f, "%s", palavra ) ==1 )
    return (palavra);
  else
    return ((char *) NULL);
}


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    exit ( 0 );
  }
  return (f);
}

/******************************************************************************
 * Readnummax()
 *
 * Arguments: f2 - the file sent
 *            num_max - the vector to change
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/
void Readnummax(FILE * f2, int * num_max){
  int i, a;
  char str1[100] = "\0";
  char str2[100] = "\0";

  for (i = 0; i < 100; i++)
    num_max[i] = 0;

  while (fscanf(f2, "%s %s %d", str1, str2, &i) != EOF) {
  	a = charcmp(str1,str2,i);
    if (a > num_max[strlen(str1) - 1] && a <= i)
    {
    	num_max[strlen(str1) - 1] = a;
    }
    else if (i > num_max[strlen(str1) - 1] && a > i)
    {
    	num_max[strlen(str1) - 1] = i;
    }
  }
}

/******************************************************************************
 * charcmp
 *
 * Arguments: arg1 - first string
 *            arg2 - second string
 *        num_letras_max - number of maximum change in one iteration
 * Returns: number of diferent letters between the two strings
 * Side-Effects: none
 *
 *****************************************************************************/
int charcmp(char* arg1, char* arg2, int num_letras_max) {
  int i = 0, letras_dif = 0;
  for (i = 0; i < strlen(arg1); i++) {
    if (arg1[i] != arg2[i])
      letras_dif++;
    if( letras_dif > num_letras_max)
      break;
  }
  return letras_dif;
}
