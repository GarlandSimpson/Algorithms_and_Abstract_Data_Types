/*
	Name: Garland Simpson
	cruz-id: gfsimpso
	Assignment: pa4

    --This is a test program for Graph ADT
*/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {

	
	
	//Create a graph with multiple elements C
	fprintf(stdout, "%s", "\n\n--- GraphTest for graph ADT ---\n\n");

	
	Graph B = newGraph(6); // Create an undirected graph B with 6 vertices
	Graph C = newGraph(6); // Create an directed graph C with 6 vertices
	Graph D = newGraph(2); // Create an undirected graph D with 2 vertices
	Graph E = newGraph(2); // Create an directed graph D with 2 vertices
	

	fprintf(stdout, "%s", "\n--- Construct Undirected Graph:\n");
	addEdge(B, 1, 2);
	addEdge(B, 1, 5);
	addEdge(B, 2, 3);
	addEdge(B, 2, 5);
	addEdge(B, 3, 4);
	addEdge(B, 3, 5);
	addEdge(B, 4, 6);
	addEdge(B, 5, 6);

	printGraph(stdout, B); // Print Undirected Graph

	fprintf(stdout, "%s", "\n--- Call getSource(B)= ");
	if (getSource(B) == 0) 
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getSource(B));
	fprintf(stdout, "%s", "\n--- Call getDist(B, 3)= ");
	if (getDist(B, 3) == -1)
		fprintf(stdout, "%s", "INF");
	else
		fprintf(stdout, "%d", getDist(B, 3));
	fprintf(stdout, "%s", "\n--- Call getParent(B, 3)= ");
	if (getParent(B, 3) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getParent(B, 3));
	fprintf(stdout, "%s", "\n");

	fprintf(stdout, "%s", "\n--- Call BFS(B, 3):\n");
	BFS(B, 3);

	int order = getOrder(B);
	for (int v = 1; v <= order; v++) {
		fprintf(stdout, "%d", v);
		fprintf(stdout, ": ");
		fprintf(stdout, "%s", " d[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		fprintf(stdout, "%d", getDist(B, v));
		fprintf(stdout, "%s", ", p[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		if (getParent(B, v) == 0)
			fprintf(stdout, "%s", "NIL");
		else
			fprintf(stdout, "%d", getParent(B, v));
		fprintf(stdout, "%s", "\n");
	}
	fprintf(stdout, "%s", "\n--- Call getSource(B)= ");
	fprintf(stdout, "%d", getSource(B));
	fprintf(stdout, "%s", "\n--- Call getSize(B)= ");
	fprintf(stdout, "%d", getSize(B));
	fprintf(stdout, "%s", "\n--- Call getOrder(B)= ");
	fprintf(stdout, "%d", getOrder(B));


	fprintf(stdout, "%s", "\n\n\n\n--- Construct Directed Graph:\n");
	addArc(C, 1, 2);
	addArc(C, 1, 5);
	addArc(C, 2, 5);
	addArc(C, 3, 2);
	addArc(C, 3, 5);
	addArc(C, 4, 3);
	addArc(C, 5, 6);
	addArc(C, 6, 4);

	printGraph(stdout, C); // Print Directed Graph

	fprintf(stdout, "%s", "\n--- Call getSource(C)= ");
	if (getSource(C) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getSource(C));
	fprintf(stdout, "%s", "\n--- Call getDist(C, 3)= ");
	if (getDist(C, 3) == -1)
		fprintf(stdout, "%s", "INF");
	else
		fprintf(stdout, "%d", getDist(C, 3));
	fprintf(stdout, "%s", "\n--- Call getParent(C, 3)= ");
	if (getParent(C, 3) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getParent(C, 3));
	fprintf(stdout, "%s", "\n");

	fprintf(stdout, "%s", "\n--- Call BFS(C, 3):\n");
	BFS(C, 3);

	order = getOrder(C);
	for (int v = 1; v <= order; v++) {
		fprintf(stdout, "%d", v);
		fprintf(stdout, ": ");
		fprintf(stdout, "%s", " d[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		if (getDist(C, v) == -1)
			fprintf(stdout, "%s", "INF");
		else
			fprintf(stdout, "%d", getDist(C, v));
		fprintf(stdout, "%s", ", p[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		if (getParent(C, v) == 0)
			fprintf(stdout, "%s", "NIL");
		else
			fprintf(stdout, "%d", getParent(C, v));
		fprintf(stdout, "%s", "\n");
	}
	fprintf(stdout, "%s", "\n--- Call getSource(C)= ");
	fprintf(stdout, "%d", getSource(C));
	fprintf(stdout, "%s", "\n--- Call getSize(C)= ");
	fprintf(stdout, "%d", getSize(C));
	fprintf(stdout, "%s", "\n--- Call getOrder(C)= ");
	fprintf(stdout, "%d", getOrder(C));
	fprintf(stdout, "%s", "\n");


	fprintf(stdout, "%s", "\n\n\n--- Construct Undirected Graph:\n");
	addEdge(D, 1, 2);

	printGraph(stdout, D); // Print Undirected Graph

	fprintf(stdout, "%s", "\n--- Call getSource(D)= ");
	if (getSource(D) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getSource(D));
	fprintf(stdout, "%s", "\n--- Call getDist(D, 2)= ");
	if (getDist(D, 2) == -1)
		fprintf(stdout, "%s", "INF");
	else
		fprintf(stdout, "%d", getDist(D, 2));
	fprintf(stdout, "%s", "\n--- Call getParent(D, 2)= ");
	if (getParent(D, 2) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getParent(D, 2));
	fprintf(stdout, "%s", "\n");

	fprintf(stdout, "%s", "\n--- Call BFS(D, 2):\n");
	BFS(D, 2);

	order = getOrder(D);
	for (int v = 1; v <= order; v++) {
		fprintf(stdout, "%d", v);
		fprintf(stdout, ": ");
		fprintf(stdout, "%s", " d[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		fprintf(stdout, "%d", getDist(D, v));
		fprintf(stdout, "%s", ", p[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		if (getParent(D, v) == 0)
			fprintf(stdout, "%s", "NIL");
		else
			fprintf(stdout, "%d", getParent(D, v));
		fprintf(stdout, "%s", "\n");
	}
	fprintf(stdout, "%s", "\n--- Call getSource(D)= ");
	fprintf(stdout, "%d", getSource(D));
	fprintf(stdout, "%s", "\n--- Call getSize(D)= ");
	fprintf(stdout, "%d", getSize(D));
	fprintf(stdout, "%s", "\n--- Call getOrder(D)= ");
	fprintf(stdout, "%d", getOrder(D));
	fprintf(stdout, "%s", "\n");

	fprintf(stdout, "%s", "\n\n\n--- Construct Directed Graph:\n");
	addArc(E, 1, 2);

	printGraph(stdout, E); // Print Directed Graph

	fprintf(stdout, "%s", "\n--- Call getSource(E)= ");
	if (getSource(E) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getSource(E));
	fprintf(stdout, "%s", "\n--- Call getDist(E, 2)= ");
	if (getDist(E, 2) == -1)
		fprintf(stdout, "%s", "INF");
	else
		fprintf(stdout, "%d", getDist(E, 2));
	fprintf(stdout, "%s", "\n--- Call getParent(E, 2)= ");
	if (getParent(E, 2) == 0)
		fprintf(stdout, "%s", "NIL");
	else
		fprintf(stdout, "%d", getParent(E, 2));
	fprintf(stdout, "%s", "\n");

	fprintf(stdout, "%s", "\n--- Call BFS(E, 2):\n");
	BFS(E, 2);

	order = getOrder(E);
	for (int v = 1; v <= order; v++) {
		fprintf(stdout, "%d", v);
		fprintf(stdout, ": ");
		fprintf(stdout, "%s", " d[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		fprintf(stdout, "%d", getDist(E, v));
		fprintf(stdout, "%s", ", p[");
		fprintf(stdout, "%d", v);
		fprintf(stdout, "%s", "]= ");
		if (getParent(E, v) == 0)
			fprintf(stdout, "%s", "NIL");
		else
			fprintf(stdout, "%d", getParent(E, v));
		fprintf(stdout, "%s", "\n");
	}
	fprintf(stdout, "%s", "\n--- Call getSource(E)= ");
	fprintf(stdout, "%d", getSource(E));
	fprintf(stdout, "%s", "\n--- Call getSize(E)= ");
	fprintf(stdout, "%d", getSize(E));
	fprintf(stdout, "%s", "\n--- Call getOrder(E)= ");
	fprintf(stdout, "%d", getOrder(E));
	fprintf(stdout, "%s", "\n");

	freeGraph(&B);
	freeGraph(&C);
	freeGraph(&D);
	freeGraph(&E);

	/*---Uncomment if needed---*/
	//system("Pause"); 
	return(0);
}
