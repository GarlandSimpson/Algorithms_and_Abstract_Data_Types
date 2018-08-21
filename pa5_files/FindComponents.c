// Finds the strongly connected components of a Graph ADT using Adjacency Lists.
//
// Name: Garland F. Simpson
// cruz-id: gfsimpso
// Assignment: pa5
//
//-----------------------------------------------------------------------------


#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 160
//#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
int main(int argc, char *argv[]) {

	FILE *in, *out = NULL;
	char line[MAX_LEN] = {};
	int n;
	int cnt = 0;
	int tokenlist[MAX_LEN] = {};
	char *token;

	/* check command line for correct number of arguements */
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	/* open files for reading and writing */
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
	}

	Graph G = NULL;
	List S = newList();

	/* read input from file, convert asci to int and addArc */
	while (fgets(line, MAX_LEN, in) != NULL) {
		n = 0;
		token = strtok(line, " \n");

		while (token != NULL) {
			if (cnt == 0)
				G = newGraph(atoi(token));
			else
				tokenlist[n++] = atoi(token);
			token = strtok(NULL, " ");
		}
		if (tokenlist[0] == 0 && tokenlist[1] == 0)
			break;
		if (cnt != 0) {
			addArc(G, tokenlist[0], tokenlist[1]);
		}
		cnt++;
	}

	/* fill our vertex list */
	n = getOrder(G);
	for (int u = 1; u <= n; u++) append(S, u);

	/* print adjacency list */
	fprintf(out, "%s", "Adjacency list representation of G:\n");
	printGraph(out, G);

	/* build graph G and its tranpose T */
	DFS(G, S);
	Graph T = transpose(G);
	DFS(T, S);

	/* do fancy strongly connected component calculations */
	moveBack(S);
	n = getCcs(T);
	List L = newList();

	fprintf(out, "\nG contains %i strongly connected components:\n", n);
	for (int i = 1; i <= n; i++) {

		fprintf(out, "Component %i: ", i);
		while (index(S) >= 0 && getParent(T, get(S)) != 0) {
			prepend(L, get(S));
			deleteBack(S);
		}
		prepend(L, get(S));
		deleteBack(S);
		printList(out, L);
		clear(L);
		fprintf(out, "\n");
	}

	/* free heap objects */
	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);
	freeList(&L);

	/* close files */
	fclose(in);
	fclose(out);

	return(0);
	//system("Pause"); // This is used to pause terminal screen for visual studios
}