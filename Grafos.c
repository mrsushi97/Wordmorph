#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "LinkedList.h"
#include "ficheiros.h"
#include "Grafos.h"
#include "defs.h"

struct LinkedListStruct { Item this; LinkedList * next; };
struct graph { int V; int E; LinkedList **adj; };
struct edge { int v; int w; };



/******************************************************************************
 * GRAPHinit
 *
 * Arguments: V - integer with number of vertices
 * Returns: pointer to graph
 * Side-Effects: exit if there is no memory for allocation
 *
 *****************************************************************************/
Graph *GRAPHinit(int V)
{
	int i;
	Graph *G;

	G = (Graph*)malloc(sizeof(Graph));
	if (G == NULL){
		exit(0);
	}
	G->V = V;
	G->E = 0;
	G->adj = (LinkedList **)malloc(sizeof(LinkedList*)*V);
	for (i = 0; i < V; i++)
		G->adj[i] = initLinkedList();
	return G;
}

/******************************************************************************
 * CriaEdge
 *
 * Arguments: v - destination vertice vertice
 *            w - edge weight
 * Returns: the newly created edge
 * Side-Effects: exit if there is no memory for allocation
 *
 *****************************************************************************/
Edge *CriaEdge(int v,int w){
	Edge* NovaEdge = (Edge* )malloc(sizeof(Edge));
	if(NovaEdge == NULL){
		exit(0);
	}
	NovaEdge->v = v;
	NovaEdge->w = w;

	return NovaEdge;
}


/******************************************************************************
 * GRAPHinsertE
 *
 * Arguments: G - graph to insert the edge
 *            v_source - source vertice
 *			  v_dest - destination vertice
 *			  w - weight of the edge
 * Returns: (none)
 * Side-Effects: none
 *
 *****************************************************************************/
void GRAPHinsertE(Graph *G, int v_source, int v_dest,int w)
{
	Edge* Newnode = CriaEdge(v_dest,w);
	G->adj[v_source] = insertUnsortedLinkedList(G->adj[v_source], Newnode);

	Newnode = CriaEdge(v_source,w);
	G->adj[v_dest] = insertUnsortedLinkedList(G->adj[v_dest], Newnode);
	G->E++;

}

/******************************************************************************
 * CriaGrafos
 *
 * Arguments: arg2 - .pal file name
 *            Tabelapalavras - organized word table
 *			  max_lenght_palavra - integer with the max string length
 *			  lenght_vector - vector with the number of words for each string length
 * Returns: A pointer to a graph vector
 * Side-Effects: exits if no memory or fails to open file
 *
 *****************************************************************************/
Graph **CriaGrafos( char * arg2, char*** Tabelapalavras, int max_lenght_palavra, int* lenght_vector, int *num_letras_max) {
	Graph **G= NULL;
	int i,j,x,ldif,w;

	G=(Graph**)malloc(sizeof(Graph*)*max_lenght_palavra);
	if(G == NULL){
		exit(0);
	}

	for (i = 0; i < max_lenght_palavra; i++) {
		G[i] = GRAPHinit(lenght_vector[i]);
	}

	for (i = 0; i < max_lenght_palavra; i++){
		for (j = 0; j < lenght_vector[i] && num_letras_max[i]>0; j++) {
			for (x = j+1; x < lenght_vector[i]; x++) {

				ldif = charcmp(Tabelapalavras[i][j], Tabelapalavras[i][x], num_letras_max[i]);
				if (ldif <= num_letras_max[i]) {
					w = ldif*ldif;
					GRAPHinsertE(G[i], j, x, w);
				}
			}
		}
	}
	return G;
}

/******************************************************************************
 * destroyEdge
 *
 * Arguments: item - edge's item
 * Returns: none
 * Side-Effects: none
 *
 *****************************************************************************/
void destroyEdge( Item item ){
	free((Edge*)item);
}

/******************************************************************************
 * freeStuff
 *
 * Arguments: G - a graph
 * Returns: none
 * Side-Effects: none
 *
 *****************************************************************************/
void freeStuff(Graph *G)
{
	int i;
	for (i = 0; i < G->V; i++)
	{
			freeLinkedList(G->adj[i],&destroyEdge);
	}
	free(G->adj);
	free(G);
	return;
}
