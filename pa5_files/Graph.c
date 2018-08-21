// Name: Garland F. Simpson
// cruz-id: gfsimpso
// Assignment: pa5
//
//-----------------------------------------------------------------------------
#include "Graph.h"


typedef struct GraphObj {
	List *adj;
	int *color;
	int *p;
	int *d;
	int *f;

	int order;
	int size;
	int ccs;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {

	Graph G = malloc(sizeof(GraphObj));
	G->adj = (List *)malloc((n + 1) * sizeof(List));
	G->color = (int *)malloc((n + 1) * sizeof(int));
	G->p = (int *)malloc((n + 1) * sizeof(int));
	G->d = (int *)malloc((n + 1) * sizeof(int));
	G->f = (int *)malloc((n + 1) * sizeof(int));


	for (int u = 1; u <= n; u++) {
		G->adj[u] = newList();
	}

	G->order = n;
	G->size = 0;
	G->ccs = 0;

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
		free((*pG)->f);
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/
int getOrder(Graph G) {

	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph");
		exit(1);
	}
	return G->order;
}

int getSize(Graph G) {

	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph");
		exit(1);
	}
	return G->size;
}

int getCcs(Graph G) {

	if (G == NULL) {
		printf("Graph Error: calling getCcs() on NULL Graph reference\n");
		exit(1);
	}
	return G->ccs;
}

int getParent(Graph G, int u) {/* Pre: 1<=u<=n=getOrder(G) */

	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph ");
		exit(1);
	}

	if (1 <= u && u <= getOrder(G)) {
		return G->p[u];
	}
	return NIL;
}

int getDiscover(Graph G, int u) {   /* Pre: 1<=u<=n=getOrder(G) */

	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph ");
		exit(1);
	}

	if (1 <= u && u <= getOrder(G)) {
		return G->d[u];
	}
	return UNDEF;
}

int getFinish(Graph G, int u) {   /* Pre: 1<=u<=n=getOrder(G) */

	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph ");
		exit(1);
	}

	if (1 <= u && u <= getOrder(G)) {
		return G->f[u];
	}
	return UNDEF;
}

/*** Manipulation procedures ***/
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

void Visit(Graph G, List *L, int u, int *time) {

	*time = *time + 1; //time = time + 1
	G->d[u] = *time; //u.d  = time
	G->color[u] = 2; //u.color = GRAY

	List V = G->adj[u];

	for(moveFront(V); index(V) >= 0; moveNext(V)) { //for each v in G.Adj[u]
		
		if (G->color[get(V)] == 1) { //if v.color == WHITE
			G->p[get(V)] = u; //v.pi = u
			Visit(G, L, get(V), time); //Visit(G, v)
		}
	}

	G->color[u] = 3; //u.color = BLACK
	*time = *time + 1;//time = time + 1
	G->f[u] = *time; //u.f = time

	moveFront(*L);
	while (get(*L) != u) moveNext(*L);
	delete(*L);
	prepend(*L, u);
}

void DFS(Graph G, List S) {    /* Pre: length(S)==getOrder(G) */
	// for each vertex u in G.V
	if (length(S) == getOrder(G)) {

		for(moveFront(S); index(S) >= 0; moveNext(S)) {
			G->color[get(S)] = 1; //u.color = WHITE
			G->p[get(S)] = NIL; //u.pi = NIL
		}

		int time = 0; //time = 0

		moveFront(S);
		//for each vertex u in G.V
		for(moveFront(S); index(S) >= 0; moveNext(S)) {
			
			if (G->color[get(S)] == 1) {//if u.color == WHITE
				Visit(G, &S, get(S), &time); //DFS-Visit(G, u)
				moveFront(S);
				G->ccs++;
			}

		}
	}
}

/* Other Functions */ 
Graph transpose(Graph G) {
	int order = getOrder(G);
	Graph T = newGraph(order);
	List V;

	for (int u = 1; u <= order; u++) {
		V = G->adj[u];
		for (moveFront(V); index(V) >= 0; moveNext(V)) {
			addArc(T, get(V), u);
		}
		
	}
	return T;
}

Graph copyGraph(Graph G) {
	int order = getOrder(G);
	Graph C = newGraph(order);
	List V;

	for (int u = 1; u <= order; u++) {
		
		V = G->adj[u];
		for (moveFront(V); index(V) >= 0; moveNext(V)) {
			addArc(C, u, get(V));
		}
	}
	return C;
}

void printGraph(FILE* out, Graph G) {

	if (G == NULL) {
		printf("Graph Error: calling printGraph() on a NULL graph reference");
		exit(1);
	}
	int order = getOrder(G);
	for (int u = 1; u <= order; u++) {
		fprintf(out, "%d%s", u, ": ");
		printList(out, G->adj[u]);
		fprintf(out, "%s", "\n");
	}
}