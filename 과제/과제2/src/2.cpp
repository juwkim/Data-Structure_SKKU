#include <stdio.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

typedef char Data;
typedef struct {
	int	front, rear;
	Data items[1000];
} Queue;

/* Make a queue empty */
void InitQueue(Queue* pqueue)
{
	pqueue->front = pqueue->rear = 0;
}

/* Check whether a queue is full */
bool IsFull(Queue* pqueue, int lenQue)
{
	return pqueue->front == (pqueue->rear + 1) % lenQue;
}

/* Check whether a queue is empty */
bool IsEmpty(Queue* pqueue)
{
	return pqueue->front == pqueue->rear;
}

/* Read the item at the front */
Data Peek(Queue* pqueue)
{
	return pqueue->items[pqueue->front];
}


/* Insert an item at the rear */
int EnQueue(Queue* pqueue, Data item, int lenQue)
{
	if (IsFull(pqueue, lenQue)) return 0;
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1) % lenQue;
	return 1;
}

/* Delete an item at the front */
int DeQueue(Queue* pqueue, int lenQue)
{
	if (IsEmpty(pqueue)) return 0;
	pqueue->front = (pqueue->front + 1) % lenQue;
	return 1;
}


int main() {
	Queue qu;
	InitQueue(&qu);

	int num, lenQue, t, i, sum = 0;
	int *s, *p;

	scanf("%d %d %d", &num, &lenQue, &t);
	s = (int*)malloc(sizeof(int) * num);
	p = (int*)malloc(sizeof(int) * num);

	for (i = 0; i < num; i++) scanf("%d", p + i);

	for (i = 0; i < num; i++) {
		if (i >= t && *(s+i-t)==1) {
			sum -= Peek(&qu);
			DeQueue(&qu, 1000);
		}

		sum += *(p + i);
		if (sum <= lenQue) {
			EnQueue(&qu, *(p + i), 1000);
			printf("%d ", 1);
			*(s+i) = 1;
		}
		else {
			sum -= *(p + i);
			printf("%d ", 0);
			*(s+i) = 0;
		}
	}
	free(p);
	free(s);
}