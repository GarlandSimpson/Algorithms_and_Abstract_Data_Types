// Name: Garland Simpson
// cruz-id: gfsimpso
// Assignment: pa4
//
//-----------------------------------------------------------------------------
#include "Graph.h"


typedef struct GraphObj {
	List *adj;
	int *color;
	int *p;
	int *d;

	int order;
	int size;
	int src;

} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	
	Graph G = malloc(sizeof(GraphObj));
	G->adj = (List *)malloc((n+1)* sizeof(List));
	G->color = (int *)malloc((n+1)* sizeof(int));
	G->p = (int *)malloc((n+1)* sizeof(int));
	G->d = (int *)malloc((n+1)* sizeof(int));

	for (int u = 1; u <= n; u++) { // was u = 1
		G->adj[u] = newList();
		G->color[u] = NIL;
		G->p[u] = NIL;
		G->d[u] = INF;
	}

	G->order = n;
	G->size = 0;
	G->src = NIL;
	
	return(G);
}

void freeGraph(Graph* pG) {

	if (pG != NULL && *pG != NULL) {

		List L;
		for (int i = 1; i <= getOrder(*pG); i++) {
			L = (*pG)->adj[i];
			freeList(&L);
		}

		free((*pG)->color);
		free((*pG)->adj);
		free((*pG)->d);
		free((*pG)->p);
		free(*pG);
		pG = NULL;
	}
}

/*** Access functions ***/
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return(G->order);
}

int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return(G->size);
}

int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	return (G->src);
}

int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	else if (1 > u || u > G->order) {
		printf("Graph Error: calling getParent() on u not in range 1 <= u <= getOrder(G)\n");
		exit(1);
	}
	return G->p[u];
}

int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	else if (1 > u || u > G->order) {
		printf("Graph Error: calling getDist() on u not in range 1 <= u <= getOrder(G)\n");
		exit(1);
	}
	return G->d[u];
}

void getPath(List L, Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(1);
	}
	else if (L == NULL) {
		printf("Graph Error: calling getPath() on NULL List reference\n");
		exit(1);
	}
	else if (1 > u || u > G->order) {
		printf("Graph Error: calling getPath() on u not in range 1 <= u <= getOrder(G)\n");
		exit(1);
	}
	else if (getSource(G) == NIL) {
		printf("Graph Error: calling getSource() before BFS()\n");
		exit(1);
	}
	else if (getSource(G) == u)
		append(L, u);
	else if (G->p[u] != NIL) {
		getPath(L, G, G->p[u]);
		append(L, u);
	}
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(1);
	}

	for (int u = 1; u <= getOrder(G); u++) {
		clear(G->adj[u]);
		G->color[u] = NIL;
		G->p[u] = NIL;
		G->d[u] = INF;
	}
	G->src = NIL;
	G->size = 0;
}

void addEdge(Graph G, int u, int v) {

	if (1 > u || u > G->order) {
		printf("Graph Error: calling addEdge() u is out of range 1<= u <= getOrder(G)\n");
		exit(1);
	}
	else if (1 > v || v > G->order) {
		printf("Graph Error: calling addEdge() v is out of range 1<= v <= getOrder(G)\n");
		exit(1);
	}

	// Add u to vertex list v
	if (length(G->adj[v]) == 0 || u <= front(G->adj[v]))
		prepend(G->adj[v], u);

	else if (u >= back(G->adj[v]))
		append(G->adj[v], u);

	else if (front(G->adj[v]) < u && back(G->adj[v]) > u) {
		moveFront(G->adj[v]);

		while (get(G->adj[v]) <= u)
			moveNext(G->adj[v]);
		insertBefore(G->adj[v], u);
	}

	// Add v to vertex list u
	if (length(G->adj[u]) == 0 || v <= front(G->adj[u]))
		prepend(G->adj[u], v);

	else if (v > back(G->adj[u]))
		append(G->adj[u], v);

	else if (front(G->adj[u]) < v && back(G->adj[u]) > v) {
		moveFront(G->adj[u]);

		while (get(G->adj[u]) < v)
			moveNext(G->adj[u]);
		insertBefore(G->adj[u], v);
	}
	G->size++;
}

void addArc(Graph G, int u, int v) {
	if (1 > u || u > G->order) {
		printf("Graph Error: calling addEdge() u is out of range 1<= u <= getOrder(G)\n");
		exit(1);
	}
	else if (1 > v || v > G->order) {
		printf("Graph Error: calling addEdge() v is out of range 1<= v <= getOrder(G)\n");
		exit(1);
	}
	// Add v to vertex list u
	if (length(G->adj[u]) == 0 || v <= front(G->adj[u]))
		prepend(G->adj[u], v);

	else if (v > back(G->adj[u]))
		append(G->adj[u], v);

	else if (front(G->adj[u]) < v && back(G->adj[u]) > v) {
		moveFront(G->adj[u]);

		while (get(G->adj[u]) < v)
			moveNext(G->adj[u]);
		insertBefore(G->adj[u], v);
	}
	G->size++;
}

void BFS(Graph G, int s) {
	if (1 > s || s > getOrder(G)) {
		printf("Graph Error: calling BFS() s is out of range 1<= s <= getOrder(G)\n");
		exit(1);
	}
	G->src = s;
	int u;
	for (u = 1; u <= getOrder(G); u++) {
		if (u != s) {
			G->color[u] = 1; // 1 = WHITE
			G->d[u] = INF;
			G->p[u] = NIL;
		}
	}

	G->color[s] = 2; // 2 = GRAY
	G->d[s] = 0;
	G->p[s] = NIL;

	List Q = newList();
	append(Q, s);
	int v;

	while (length(Q) > 0) {  // change to for loop

		u = front(Q);
		deleteFront(Q);
		moveFront(G->adj[u]); 

		while(index(G->adj[u]) >= 0) {
			v = get(G->adj[u]);

			if (G->color[v] == 1) { // 1 = WHITE
				G->color[v] = 2; // 2 = GRAY
				G->d[v] = G->d[u] + 1; 
				G->p[v] = u;
				append(Q, v);
			}
			moveNext(G->adj[u]);
		}
		G->color[u] = 3; // 3 = BLACK
	}
	freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(1);
	}

	int n = getOrder(G);
	for(int u = 1; u <= n; u++) { // possibly < n
		fprintf(out,"%d", u);
		fprintf(out,": ");
		printList(out, G->adj[u]);
		fprintf(out,"\n");
	}
}