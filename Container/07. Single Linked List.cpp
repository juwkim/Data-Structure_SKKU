#include <stdlib.h>
#include <stdio.h>

typedef int Data;
typedef struct _Node {
	Data item;
	struct _Node* next;
} Node;

typedef struct {
	Node* head;
	int len;
} LinkedList;

// Make a list empty.
void InitList(LinkedList* plist) {
	// Create a dummy node;
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->len = 0;
}

// Check whether the list is empty.
bool IsEmpty(LinkedList* plist) {
	return plist->len == 0;
}

// Insert an item at the k-th position.
void InsertMiddle(LinkedList* plist, int pos, Data item) {
	Node* cur, * newNode;
	if (pos < 0 || pos > plist->len) exit(1);
	// Create a new node.
	newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = NULL;
	// Move the cur pointer to the (k-1)-th position.
	cur = plist->head;
	for (int i = 0; i < pos; i++)
		cur = cur->next;
	// Insert the new node to the k-th position.
	newNode->next = cur->next;
	cur->next = newNode;
	plist->len++;
}

// Remove an item at the k-th position.
void RemoveMiddle(LinkedList* plist, int pos) {
	Node* cur, * temp;
	if (IsEmpty(plist) || pos < 0 || pos >= plist->len) exit(1);

	// Move the cur pointer to the (k-1)-th position.
	cur = plist->head;
	for (int i = 0; i < pos; i++) cur = cur->next;

	// Remove the node to the k-th position.
	temp = cur->next;
	cur->next = cur->next->next;
	plist->len--;
	free(temp);
}

void RemoveFirst(LinkedList* plist) {
	Node* head = plist->head;
	Node* temp;
	if (IsEmpty(plist)) exit(1);

	temp = head->next;
	head->next = head->next->next;
	plist->len--;
	free(temp);
}

// Read an item at the k-th position.
Data ReadItem(LinkedList* plist, int pos) {
	Node* cur;
	if (IsEmpty(plist) || pos < 0 || pos >= plist->len) exit(1);

	// Move the cur pointer to the k-th position.
	cur = plist->head->next;
	for (int i = 0; i < pos; i++) cur = cur->next;

	return cur->item;
}

// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next) printf("%d\n", cur->item);
}

// Remove all nodes in a list in sequence.
void ClearList(LinkedList* plist) {
	while (plist->head->next != NULL) RemoveFirst(plist);
	free(plist->head);
}

LinkedList* Concatenate(LinkedList* plist1, LinkedList* plist2) {
	if (plist1->head->next == NULL) return plist2;
	else if (plist2->head->next == NULL) return plist1;
	else {
		// Move the current pointer to the last position.
		Node* cur = plist1->head->next;
		while (cur->next != NULL)
			cur = cur->next;
		// Link the current pointer to the second list.
		cur->next = plist2->head->next;
		// Remove the dummy node from the second list.
		free(plist2->head);
		return plist1;
	}
}

// Make the list in reverse sequence.
void Reverse(LinkedList* plist) {
	Node* prev = NULL, * cur = NULL;
	Node* next = plist->head->next;
	// Repeat the next node is NULL.
	while (next != NULL) {
		// Set the previous, current, and next nodes.
		prev = cur;
		cur = next;
		next = next->next;
		// Change the link of the current node.
		cur->next = prev;
	}
	// Connect the dummy node to the current node.
	plist->head->next = cur;
}