//-----------------------------------------------------------------------------
// Name: Garland Simpson
// cruz-id: gfsimpso
// Assignment: pa2
//
// Lex.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------




#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include "List.h"
#define MAX_LEN 160
//#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
// deprecated code here

int main(int argc, char * argv[]) {

	int i, count = 0;
	FILE *in, *out;
	char line[MAX_LEN];
	char ar[MAX_LEN][256];
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

	
	/* read each line of input file, then count and print tokens */
	
	
	while (fgets(line, MAX_LEN, in) != NULL) {
		strcpy(ar[count], line);
		count++;
	}
	token = strcat(line, " \n");
	strcpy(ar[count - 1], line);
	
	

	List myList = newList();

	append(myList, 0);

	for (i = 1; i < count; i++)
	{
		for (moveFront(myList); index(myList) >= 0; moveNext(myList))
		{
			if (strcmp(ar[i], ar[get(myList)]) < 0)
			{
				insertBefore(myList, i);
				break;
			}
		}

		if (index(myList) == -1)
			append(myList, i);
	}
	for (moveFront(myList); index(myList) >= 0; moveNext(myList))
	{
		fprintf(out, "%s", ar[get(myList)]);
		
	}
	freeList(&myList);
	/* close files */
	fclose(in);
	fclose(out);


	return(0);
}