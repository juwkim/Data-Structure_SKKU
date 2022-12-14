#include <stdlib.h>

typedef int Data;
typedef struct _Node {
	Data item;
	struct _Node* next;
} Node;

typedef struct {
	Node* tail;
	int len;
} CircularList;

void InsertInitItem(CircularList* plist, Data item) {
	// Create a new node.
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = newNode;

	plist->tail = newNode;
	plist->len++;
}

void InsertFirst(CircularList* plist, Data item) {
	if (plist->len == 0)
		InsertInitItem(plist, item);
	else {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->item = item;
		newNode->next = plist->tail->next;

		// Connect the back node to the new node.
		plist->tail->next = newNode;
		plist->len++;
	}
}

void InsertLast(CircularList* plist, Data item) {
	if (plist->len == 0)
		InsertInitItem(plist, item);
	else {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->item = item;
		newNode->next = plist->tail->next;

		// Connect the back node to the new node.
		plist->tail->next = newNode;
		plist->tail = newNode;
		plist->len++;
	}
}

void InsertMiddle(CircularList* plist, int pos, Data item) {
	if (plist->len == 0)
		InsertInitItem(plist, item);
	else {
		Node* cur, * newNode;
		cur = plist->tail;
		// moving (k-1)-th position
		for (int i = 0; i < pos; i++) cur = cur->next;

		newNode = (Node*)malloc(sizeof(Node));
		newNode->item = item;
		newNode->next = cur->next;

		// linking the current node to the new node
		cur->next = newNode;
		plist->len++;
	}
}

void RemoveInitItem(CircularList* plist) {
	if (plist->len == 0) exit(1);
	else if (plist->len == 1) {
		free(plist->tail);
		plist->len--;
		plist->tail = NULL;
	}
}

void RemoveFirst(CircularList* plist) {
	if (plist->len == 1)
		RemoveInitItem(plist);
	else {
		Node* temp = plist->tail->next;
		plist->tail->next = temp->next;
		free(temp);
		plist->len--;
	}
}

void RemoveLast(CircularList* plist) {
	if (plist->len == 1)
		RemoveInitItem(plist);
	else {
		Node* cur, * temp;
		cur = plist->tail;
		for (int i = 0; i < plist->len - 1; i++)
			cur = cur->next;
		temp = cur->next;
		cur->next = temp->next;
		free(temp);
		plist->tail = cur;
		plist->len--;
	}
}

void RemoveMiddle(CircularList* plist, int pos) {
	if (plist->len == 1)
		RemoveInitItem(plist);
	else {
		Node* cur, * temp;
		cur = plist->tail;
		for (int i = 0; i < pos; i++)
			cur = cur->next;
		temp = cur->next;
		cur->next = temp->next;
		free(temp);
		plist->len--;
	}
}

