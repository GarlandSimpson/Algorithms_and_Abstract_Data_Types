// Header file for Graph ADT
// Name: Garland F. Simpson
// cruz-id: gfsimpso
// Assignment: pa5
//
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include"List.h"
#include<stdlib.h>

#define UNDEF (-1)
#define NIL 0

/*** Exported Type***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getCcs(Graph G);
int getParent(Graph G, int u);  /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);    /* Pre: length(S)==getOrder(G) */
//void Visit(Graph G, int u, int time);

/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif