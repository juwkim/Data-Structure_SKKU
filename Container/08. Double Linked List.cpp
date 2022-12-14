#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct _Node {
	Data item;
	struct _Node* prev;
	struct _Node* next;
} Node;

typedef struct {
	Node* head;
	int len;
} DoubleLinkedList;

void InitList(DoubleLinkedList* plist) {
	Node* dummy1, * dummy2;
	dummy1 = (Node*)malloc(sizeof(Node));
	dummy2 = (Node*)malloc(sizeof(Node));
	if (dummy1 && dummy2) {
		dummy1->prev = NULL;
		dummy1->next = dummy2;
		dummy2->prev = dummy1;
		dummy2->next = NULL;
		plist->head = dummy1;
		plist->len = 0;
	}
	else printf("InitList 함수에서 메모리를 정상적으로 할당하지 못했습니다.");
}

void InsertMiddle(DoubleLinkedList* plist, int pos, Data item) {
	Node* cur, * newNode;

	// Create a new node.
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->item = item;
		newNode->prev = NULL;
		newNode->next = NULL;

		// Move the cur pointer to the (k-1)-th position.
		cur = plist->head;
		for (int i = 0; i < pos; i++)
			cur = cur->next;

		// Insert the new node to the k-th position.
		newNode->prev = cur;
		newNode->next = cur->next;
		cur->next->prev = newNode;
		cur->next = newNode;
		plist->len++;
	}
	else printf("InsertMiddle 함수에서 메모리를 정상적으로 할당하지 못했습니다.");
}

void RemoveMiddle(DoubleLinkedList* plist, int pos) {
	Node* cur, * temp;
	if (plist->len==0 || pos < 0 || pos >= plist->len) exit(1);

	// Move the cur pointer to the (k-1)-th position.
	cur = plist->head;
	for (int i = 0; i < pos; i++) cur = cur->next;

	// Connect adjacent nodes to remove the k-th node.
	temp = cur->next;
	temp->next->prev = cur;
	cur->next = temp->next;

	// Remove the node to the k-th position.
	plist->len--;
	free(temp);
}

