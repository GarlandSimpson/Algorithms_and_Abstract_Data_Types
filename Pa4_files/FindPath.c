//-----------------------------------------------------------------------------
// Name: Garland Simpson
// cruz-id: gfsimpso
// Assignment: pa4
//
// FindPath.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------




#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include "Graph.h"
#define MAX_LEN 160
//#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
// deprecated code here

int main(int argc, char * argv[]) {

	int n = 0;
	int cnt = 0;
	FILE *in, *out;
	char line[MAX_LEN];
	int tokenlist[MAX_LEN];
	char* token;

	// check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	Graph G = NULL;

	while (fgets(line, MAX_LEN, in) != NULL) {
		n = 0;
		token = strtok(line, " \n");

		while (token != NULL) {
			if (cnt == 0)
				G = newGraph(atoi(token));
			else {
				tokenlist[n++] = atoi(token);
			}
			token = strtok(NULL, " ");			
		}
		if (tokenlist[0] == 0 && tokenlist[1] == 0)
			break;
		if (cnt != 0)
			addEdge(G, tokenlist[0], tokenlist[1]);
		cnt++;
	}
	printGraph(out, G);
	fprintf(out,"%s" , "\n");



	while (fgets(line, MAX_LEN, in) != NULL) {
		n = 0;
		token = strtok(line, " \n");

		while (token != NULL) {
			tokenlist[n++] = atoi(token);
			token = strtok(NULL, " ");
		}

		if (tokenlist[0] == 0 && tokenlist[1] == 0)
			break;

		List L = newList();
		BFS(G, tokenlist[0]);
		getPath(L, G, tokenlist[1]);

		if (getDist(G, tokenlist[1]) == 0 && tokenlist[0] != tokenlist[1]) {
			fprintf(out, "The distance from %i to %i is infinity\n", tokenlist[0], tokenlist[1]);
			fprintf(out, "No %i-%i path exists", tokenlist[0], tokenlist[1]);
		}
		else {
			fprintf(out, "The distance from %i to %i is %i\n", tokenlist[0], tokenlist[1], getDist(G, tokenlist[1]));
			fprintf(out, "A shortest %i-%i path is: ", tokenlist[0], tokenlist[1]);
			printList(out, L);
		}

		fprintf(out, "\n\n");
		freeList(&L);
	}

	
	/* close files */
	fclose(in);
	fclose(out);


	return(0);
}