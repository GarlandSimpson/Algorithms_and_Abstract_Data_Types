// Name: Garland Simpson
// cruz-id: gfsimpso
// Assignment: pa4


#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	int element;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int index;
	int n;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->element = data;
	N->next = N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newQueue()
// Returns reference to new empty Queue object.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->cursor = NULL;
	L->n = 0;
	L->index = -1;
	return(L);
}


void freeList(List* pL) {

	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		pL = NULL;
	}
}

// Access functions -----------------------------------------------------------
int length(List L) {

	if (L == NULL) {

		printf("Queue Error: calling getLength() on NULL Queue reference\n");
		exit(1);
	}
	return(L->n);
}

int index(List L) {
	if (L->cursor == L->front && L->index != -1)
		return 0;

	return(L->index);
}

int front(List L) {

	if (L == NULL) {

		printf("Queue Error: calling front() on NULL List reference\n");
		exit(1);
	}
	return(L->front->element);
}

int back(List L) {

	if (L == NULL) {

		printf("Queue Error: calling back() on NULL List reference\n");
		exit(1);
	}
	return(L->back->element);
}

int get(List L) {

	if (L == NULL) {

		printf("Queue Error: calling back() on NULL List reference\n");
		exit(1);
	}
	return(L->cursor->element);
}

int equals(List A, List B) {

	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}

	//CASE: List lengths not equal
	if (A->n != B->n) return 0;

	Node aTemp = A->front;
	Node bTemp = B->front;

	while (aTemp != NULL) {

		//CASE: the elements are not the same
		if (aTemp->element != bTemp->element) {

			aTemp = bTemp = NULL;
			return 0;
		}

		aTemp = aTemp->next;
		bTemp = bTemp->next;
	}

	//CASE: The lists are equal
	return 1;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L) {

	while (length(L) > 0)
		deleteBack(L);
}

void moveFront(List L) {

	if (L->n != 0) {
		L->index = 0; // L->index = L->n - 1;
		L->cursor = L->front;
	}
}

void moveBack(List L) {

	if (L->n != 0) {
		L->index = L->n - 1;
		L->cursor = L->back;
	}
}

void movePrev(List L) {

	if (L->cursor != NULL) {
		L->index--;
		L->cursor = L->cursor->prev;
	}
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing. 
}

void moveNext(List L) {

	if (L->cursor != NULL) {
		if (L->cursor == L->back) {
			L->index = -1;
			L->cursor = NULL;
		}
		else {
			L->index++;
			L->cursor = L->cursor->next;
		}

	}
}

void prepend(List L, int data) {

	Node N = malloc(sizeof(NodeObj));
	N->next = N->prev = NULL;
	N->element = data;

	//CASE: List is empty.
	if (L->front == NULL) {

		L->front = N;
		L->back = N;
		L->cursor = N;
		L->index = 0;
	}

	//CASE: List is NOT empty.
	else {
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->index++; // this is new

	}
	L->n++;
}

void append(List L, int data) {

	Node N;
	N = malloc(sizeof(NodeObj));
	N->next = NULL;
	N->prev = NULL;
	N->element = data;

	//CASE: List is empty.
	if (L->front == NULL) {

		L->front = N;
		L->back = N;
		L->cursor = N;
		L->index = 0;
	}

	//CASE: List is NOT empty.
	else {

		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}

	L->n++;
}

void insertBefore(List L, int data) {

	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling insertBefore() on an empty List\n");
		exit(1);
	}

	Node N = malloc(sizeof(NodeObj));

	N->next = NULL;
	N->prev = NULL;
	N->element = data;

	if (L->cursor->prev == NULL) {

		L->front = N;
		N->next = L->cursor;
		L->cursor->prev = N;
		L->index++;  // was L->index = 0;
	}
	else {
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor = N->prev;
		L->cursor->next = N;
		L->cursor = N->next;
		L->cursor->prev = N;
		L->index++;
	}
	L->n++;
}

void insertAfter(List L, int data) {

	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}

	Node N = malloc(sizeof(NodeObj));

	N->next = NULL;
	N->prev = NULL;
	N->element = data;

	if (L->cursor->next == NULL) {

		N->prev = L->cursor;
		L->cursor->next = N;
		L->back = N;
		L->index = 0;
	}
	else {
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
		L->cursor = N->next;
		L->cursor->prev = N;
		L->cursor = N->prev;
	}
	L->n++;
}

void deleteFront(List L) {

	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	Node N = L->front;

	if (length(L) > 1) {

		L->front = L->front->next;
		L->front->prev = NULL;
		L->cursor = L->front;
	}
	else {
		L->front = L->back = NULL;
		L->cursor = L->front;
	}

	L->n--;
	freeNode(&N);
	N=NULL;
}

void deleteBack(List L) {

	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(1);
	}

	Node N = L->back;

	if (length(L) > 1) {

		L->back = L->back->prev;
		L->back->next = NULL;
		L->cursor = L->back;
	}
	else {
		L->front = L->back = NULL;
		L->cursor = NULL;
	}

	L->n--;
	freeNode(&N);
	N=NULL;
}

void delete(List L)
{
	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling delete() on an empty List\n");
		exit(1);
	}
	Node temp = L->cursor;
	if (L->n == 1) {
		L->front = L->back = NULL;
	}
	else {
		if (L->cursor == L->front) {
			L->front = L->front->next;
			L->front->prev = NULL;

		}
		else if (L->cursor == L->back) {
			L->back = L->back->prev;
			L->back->next = NULL;
		}
		else {
			L->cursor = L->cursor->prev;
			L->cursor->next = temp->next; // this line is broken
			L->cursor = temp->next;
			L->cursor->prev = temp->prev;
		}

	}

	L->cursor = NULL;
	freeNode(&temp);
	temp = NULL;


	L->index = -1;
	L->n--;
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {

	if (L == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}
	Node temp = L->cursor;
	int idx = index(L);
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		fprintf(out, "%d ", get(L));
	}
	L->cursor = temp;
	L->index = idx;
	//fprintf(out, "%s", "\n");
}

List copyList(List L) {

	//CASE: List is NULL
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	//CASE: List is empty
	if (L->n == 0) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}

	List list = newList();

	for (moveFront(L); index(L) >= 0; moveNext(L))
		append(list, get(L));

	return(list);
}