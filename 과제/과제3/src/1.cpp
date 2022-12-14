#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define NUM 3

typedef char Data;

typedef struct _Node {
	Data item;
	struct _Node* next;
} Node;

typedef struct {
	Node* head;
	int	len;
} LinkedList;


// Make a list empty.
void InitList(LinkedList* plist) {
	// Create a dummy node;
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->len = 0;
}


// Check whether the list is empty. bool IsEmpty(LinkedList* plist)
bool IsEmpty(LinkedList* plist) {
	return plist->len == 0;
}


// Insert an item at the k-th position.
void InsertMiddle(LinkedList* plist, int *pos, Data item, Node*** cur) {
	Node *temcur, *newNode;
	int p = *pos % NUM, q = *pos / NUM;
	// Create a new node.
	newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = NULL;

	// Move the cur pointer to the (k-1)-th position.
	temcur = *(*cur + q);
	for (int i = 0; i < p; i++)
		temcur = temcur->next;

	//Insert the new node to the k-th position.
	newNode->next = temcur->next;
	temcur->next = newNode;
	plist->len++;
	(*pos)++;
}


// Remove an item at the k-th position.
void RemoveMiddle(LinkedList* plist, int* pos, Node*** cur) {
	Node * temcur, *temp;
	int p = *pos % NUM, q = *pos / NUM;
	if (*pos % NUM == 0) {
		q--;
		p = NUM;
	}
	// Move the cur pointer to the (k-1)-th position.
	temcur = *(*cur + q);
	for (int i = 0; i < p-1; i++)
		temcur = temcur->next;

	// Remove the node to the k-th position.
	temp = temcur->next;
	temcur->next = temcur->next->next;
	plist->len--;
	free(temp);
	(*pos)--;
}


// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next)
		printf("%c", cur->item);
}

int main() {
	LinkedList list;
	InitList(&list);

	int n, s = 1, count = 0;
	char opr[7] = { 0, };
	scanf_s("%d", &n);
	getchar();

	Node **cur = (Node**)malloc(sizeof(Node*)*((n/NUM) + 1));
	*cur = (&list)->head;

	for (int i = 0; i < n; i++) {
		if ((count/ NUM) >= s) {
			*(cur + s) = *(cur + s - 1);
			for (int i = 0; i < NUM; i++)
				*(cur + s) = (*(cur + s))->next;
			s++;
		}

		gets_s(opr);
		if ('m' == opr[0]) {
			if (IsEmpty(&list)) continue;
			else if ('l' == opr[5] && 0 != count) {
				count--;
			}
			else if ('r' == opr[5] && (&list)->len != count) {
				count++;
			}
		}

		else if ('a' == opr[0]) {
			if (opr[4] == '_') opr[4] = ' ';
			InsertMiddle(&list, &count, opr[4], &cur);
		}
		else {
			if (IsEmpty(&list) || count == 0) continue;
			else {
				RemoveMiddle(&list, &count, &cur);
			}
		}
		PrintList(&list);
		printf("\n");
	}
	PrintList(&list);
	return 0;
}







/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef char Data;

typedef struct _Node {
	Data item;
	struct _Node* next;
} Node;

typedef struct {
	Node* head;
	int	len;
} LinkedList;


// Make a list empty.
void InitList(LinkedList* plist) {
	// Create a dummy node;
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->len = 0;
}


// Check whether the list is empty. bool IsEmpty(LinkedList* plist)
bool IsEmpty(LinkedList* plist) {
	return plist->len == 0;
}


// Insert an item at the k-th position.
void InsertMiddle(LinkedList* plist, int* pos, Data item) {
	Node* cur, * newNode;

	// Create a new node.
	newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = NULL;

	// Move the cur pointer to the (k-1)-th position.
	cur = plist->head;
	for (int i = 0; i < *pos; i++)
		cur = cur->next;

	// Insert the new node to the k-th position.
	newNode->next = cur->next;
	cur->next = newNode;
	plist->len++;
	(*pos)++;
}


// Remove an item at the k-th position.
void RemoveMiddle(LinkedList* plist, int* pos) {
	Node* cur, * temp;

	// Move the cur pointer to the (k-1)-th position.
	cur = plist->head;
	for (int i = 0; i < *pos - 1; i++)
		cur = cur->next;

	// Remove the node to the k-th position.
	temp = cur->next;
	cur->next = cur->next->next;
	plist->len--;
	free(temp);
	(*pos)--;
}


// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next)
		printf("%c", cur->item);
}

int main() {
	LinkedList list;
	InitList(&list);

	int n, count = 0;
	char opr[7] = { 0, };
	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++) {
		gets(opr);
		if ('m' == opr[0]) {
			if (IsEmpty(&list)) continue;
			else if ('l' == opr[5] && 0 != count) count--;
			else if ('r' == opr[5] && (&list)->len != count) count++;
		}

		else if ('a' == opr[0]) {
			if (opr[4] == '_') opr[4] = ' ';
			InsertMiddle(&list, &count, opr[4]);
		}
		else {
			if (IsEmpty(&list) || count == 0) continue;
			else {
				RemoveMiddle(&list, &count);
			}
		}
	}
	PrintList(&list);
	return 0;
}*/