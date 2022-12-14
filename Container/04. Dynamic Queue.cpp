#include <stdlib.h>

typedef int Data;
typedef struct _Node {
	Data item;
	struct _Node* next;
} Node;

typedef struct {
	Node* front;
	Node* rear;
} DQueue;

// Make a queue empty.
void InitQueue(DQueue* pqueue) {
	pqueue->front = pqueue->rear = NULL;
}

// Check whether a queue is empty.
bool IsEmpty(DQueue* pqueue) {
	return pqueue->front == NULL;
}

// Read the item at the front.
Data Peek(DQueue* pqueue) {
	if (IsEmpty(pqueue)) exit(1);
	return pqueue->front->item;
}

void EnQueue(DQueue* pqueue, Data item) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;

	if (IsEmpty(pqueue))
		pqueue->front = pqueue->rear = newNode;
	else {
		pqueue->rear->next = newNode;
		pqueue->rear = newNode;
	}
}

void DeQueue(DQueue* pqueue) {
	Node* temp;
	if (IsEmpty(pqueue)) exit(1);

	temp = pqueue->front;
	if (temp->next == NULL)
		pqueue->front = pqueue->rear = NULL;
	else pqueue->front = temp->next;
	free(temp);
}

