#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "LinkedList.h"
#include "procura.h"
#include "Grafos.h"
#include "defs.h"

struct graph { int V; int E; LinkedList **adj; };
struct edge {int v; int w;};
struct heap {int free;  int *pos;int *vect; int *dist;};
struct LinkedListstruct { Item this; LinkedList * next; };

/******************************************************************************
 * printPath
 *
 * Arguments: arvore - the vector of the tree
 *            Tabelapalavras - all word's table
 *            j - integer
 *            end - the file to write
 *            dist - the vector with distances
 *            destino - identifier of the destination word
 * Returns: none
 * Side-Effects: none
 *
 * Description: prints the results
 *
 *****************************************************************************/
void printPath(int arvore[],int j, char**Tabelapalavras,FILE* end)
{
    if (arvore[j]==-1)
        return;
    printPath(arvore, arvore[j],Tabelapalavras,end);
    fprintf(end,"%s\n", Tabelapalavras[j]);

    return;
}



/******************************************************************************
 * novaheap
 *
 * Arguments: capacity - integer with the capacity
 * Returns: a pointer to the created structure type heap
 * Side-Effects: exits if failed to allocate memory
 *
 * Description:
 *
 *****************************************************************************/
heap_ * novaheap(int capacity)
{
	int i;
	heap_* heap =(heap_*) malloc(sizeof(heap_));
	if( heap == NULL)
	  exit(0);
	heap->pos = (int *)calloc(sizeof(int),capacity);
	if(heap->pos == NULL)
	  exit(0);
	heap->free = 0;
	heap->vect = (int*) calloc(sizeof(int),capacity);
	if(heap->vect == NULL)
	  exit(0);
	heap->dist = (int*) calloc(sizeof(int),capacity);
	if(heap->dist == NULL)
	  exit(0);
	for(i=0; i<capacity;i++)
	  heap->dist[i] = Infinito;
	return heap;
}

/******************************************************************************
 * Insert
 *
 * Arguments: heap - structer to insert item
 *            element - item to insert.
 * Returns: none
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
void Insert(heap_* heap, int element){
  heap->vect[heap->free] = element;
  heap->pos[element] = heap->free;
  FixUp(heap,heap->free);
  heap->free++;
}


/******************************************************************************
 * FixDown
 *
 * Arguments: heap - pointer to the structer we're going to modify
 *            index - element fixing
 * Returns: none
 * Side-Effects: none
 *
 * Description: Reorder's the heap by priority levels
 *
 *****************************************************************************/
void FixDown(heap_* heap, int index)
{
  int child, t=-1;

  while((2 * index) < (heap->free - 1)){
    child = 2*index +1;
    if(child < (heap->free -1) && heap->dist[heap->vect[child]] > heap->dist[heap->vect[child+1]]){
        child++;
    }
    /*heap condition reached*/
    if(heap->dist[heap->vect[index]] <= heap->dist[heap->vect[child]]){
      break;
    }
    heap->pos[heap->vect[index]] = child;
    heap->pos[heap->vect[child]] = index;
    t = heap->vect[index];
    heap->vect[index] = heap->vect[child];
    heap->vect[child] = t;
    index = child;
  }
}
/******************************************************************************
 * FixUp
 *
 * Arguments: heap - pointer to the structer we're going to modify
 *            index - last element
 * Returns: none
 * Side-Effects: none
 *
 * Description: Reorder's the heap by priority levels
 *
 *****************************************************************************/

void FixUp(heap_* heap, int index)
{
  int t = -1;

  while((index > 0) && heap->dist[heap->vect[(index-1)/2]] > heap->dist[heap->vect[index]]){
    heap->pos[heap->vect[index]] = (index-1)/2;
    heap->pos[heap->vect[(index-1)/2]] = index;
    t = heap->vect[index];
    heap->vect[index] = heap->vect[(index-1)/2];
    heap->vect[(index-1)/2] = t;
    index = (index-1)/2;
  }
  return;
}

/******************************************************************************
 * isEmpty
 *
 * Arguments: heap - the structure we are going to check
 * Returns: integer
 * Side-Effects: none
 *
 * Description: 1 if heap is empty 0 if it's not
 *
 *****************************************************************************/
int isEmpty(heap_* heap)
{
    return heap->free == 0;
}

/******************************************************************************
 * Minvertice
 *
 * Arguments: heap - the structure we are going to check
 *            peso_max - maximum weight/distance per connection
 *            dist - vector of distances
 * Returns: pointer to the vertice of structure type vertice
 * Side-Effects: none
 *
 * Description: get's the minimum weighted vertice, the origin
 *
 *****************************************************************************/
int Minvertice(heap_* heap)
{
    int t = -1;

  if ((heap->free) > 0){
      /*swap origin (minimum) with last then remove & return last*/
      heap->pos[heap->vect[0]] = heap->pos[heap->vect[heap->free-1]];
      heap->pos[heap->vect[heap->free-1]] = 0;
      t = heap->vect[0];
      heap->vect[0] = heap->vect[heap->free-1];
      heap->vect[heap->free-1] = t;
      --heap->free;
      FixDown(heap, 0);
  }
  return t;
}

/******************************************************************************
 * update_dist
 *
 * Arguments: heap - the structure we are going to modify
 *            v - the vertice to modify
 *            dist - the new distance/weight to update
 * Returns: none
 * Side-Effects: none
 *
 * Description: updates the distance and rearranges accordingly
 *
 *****************************************************************************/

void update_dist(heap_* heap, int v, int dist)
{
    int i = heap->pos[v];
    FixUp(heap,i);
}

/******************************************************************************
 * estanaheap
 *
 * Arguments: heap - the structure we are going to check
 *            v - the vertice we are going to check
 * Returns: boolean
 * Side-Effects: none
 *
 * Description: tell's if its on "heap"
 *
 *****************************************************************************/
bool estanaheap(heap_ *heap, int v)
{
   if (heap->pos[v] < heap->free)
     return true;
   return false;
}

/******************************************************************************
 * getpath
 *
 * Arguments: graph - the structure we are going to check
 *            origem - integer identifying origin word
 *            destino - integer identifying destination word
 *            Tabelapalavras - word's table
 *            end - the file we are going to write
 *            peso_max - condition on maximum letters iteration
 * Returns: none
 * Side-Effects: none
 *
 * Description: gets and prints the path from origin to destination
 *
 *****************************************************************************/

void getpath(Graph* graph, int origem, int destino, char** Tabelapalavras, FILE* end, int peso_max)
{
    int Ver = graph->V;
    int arvore[Ver];
    int v, u;
    heap_ *heap = novaheap(Ver);
    struct edge *vi = NULL;
    LinkedList *aux = NULL;


    /*colocar a distância do vertice origem a zero*/
    heap->dist[origem]=0;
    Insert(heap,origem);
    arvore[origem]=-1;
    u = origem;

    /*começamos a executar o algoritmo propriamente dito*/
    while (heap->free > 0 )
    {
      /*vamos buscar o vertice de menor peso*/
      u = Minvertice(heap);
      /*se ja chegamos*/
    	if(u == destino)
    		break;
      /*atualizamos a distância dos vertices adjacentes*/
      aux = graph->adj[u];
      while (aux != NULL)
      {
          vi = getItemLinkedList(aux);
          v = vi->v;
          if (heap->dist[v] == Infinito && vi->w + heap->dist[u] < heap->dist[v] && vi->w <= peso_max)
          {
              heap->dist[v] = heap->dist[u] + vi->w;
              Insert(heap,v);
              arvore[v] = u;
          }
          else if (heap->free > heap->pos[v] && vi->w + heap->dist[u] < heap->dist[v] && vi->w <= peso_max){
              heap->dist[v] = heap->dist[u] + vi->w;
              update_dist(heap, v, heap->dist[v]);
              arvore[v] = u;
          }
          aux = getNextNodeLinkedList(aux);
      }
    }

    if(heap->dist[destino] == Infinito)
      fprintf(end,"%s -1\n%s\n",Tabelapalavras[origem],Tabelapalavras[destino]);
    else
    {
      fprintf(end,"%s %d\n", Tabelapalavras[origem],heap->dist[destino]);
      printPath(arvore,destino, Tabelapalavras,end);
    }

    free(heap->dist);
    free(heap->vect);
    free(heap->pos);
    free(heap);
}

/******************************************************************************
 * procurabinaria
 *
 * Arguments: str1 - the string we are looking for
 *            length - the length of the string's vector
 *            TabelaPalavras - all words table
 * Returns: integer with the word's position (-1 if nonexistent)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int procurabinaria( char* str1, int lenght, char** Tabelapalavras){
  int min=0, max=lenght, mid=0;
  while(min <= max){
    mid = (min+max)/2;
    if(strcmp(Tabelapalavras[mid], str1) == 0){
      return mid;
    }
    else if(strcmp(Tabelapalavras[mid], str1) > 0){
      max = mid - 1;
    }
    else if(strcmp(Tabelapalavras[mid], str1) < 0){
      min = mid + 1;
    }
  }
  if(min>max)
    return -1;
  else
    return mid;
}

/******************************************************************************
 * LePal
 *
 * Arguments: pal - the .pal file name
 *            G - pointer to graph vector
 *            TabelaPalavras - all words table
 * Returns: pointer to word just read
 * Side-Effects: exits if it fails to open or create files
 *
 * Description: Reads and solves filename.pal's problems
 *
 *****************************************************************************/

void LePal(char * pal, Graph ** G, char *** TabelaPalavras, int*lvec ){
  FILE * f2, *end;
  char str1[100] = "\0", str2[100] = "\0",arg[100] = "\0";
  int Vertice1,Vertice2, nletters,peso_max;

  f2 = fopen(pal, "r");
  if( f2 == NULL)
    exit(0);
  strncpy(arg,pal,strlen(pal)-4);
  strcat(arg,".path");
  end =fopen(arg,"w");
  if( end == NULL)
    exit(0);

  while(fscanf(f2, "%s %s %d", str1, str2, &nletters) != EOF){
    peso_max = nletters*nletters;
    if(strcmp(str1,str2) == 0)
      fprintf(end, "%s 0\n%s\n",str1,str2);
    else{
      Vertice1 = procurabinaria(str1,lvec[strlen(str1) - 1], TabelaPalavras[strlen(str1) -1]);
      Vertice2 = procurabinaria(str2,lvec[strlen(str2) - 1], TabelaPalavras[strlen(str2) -1]);
      getpath(G[strlen(str1) -1], Vertice1, Vertice2,TabelaPalavras[strlen(str1)-1],end,peso_max);
    }
    fprintf(end,"\n");
  }
  fclose(f2);
  fclose(end);
}
