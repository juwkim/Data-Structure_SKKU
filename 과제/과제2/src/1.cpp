#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

typedef char Data;
typedef struct {
	int	front, rear;
	Data items[10000];
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

bool IsOne(Queue* pqueue, int lenQue)
{
	if (pqueue->rear > pqueue->front)
		return pqueue->rear - pqueue->front == 1;
	else return (pqueue->front - pqueue->rear) == lenQue - 1;
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
	else
	{
		pqueue->items[pqueue->rear] = item;
		pqueue->rear = (pqueue->rear + 1) % lenQue;
	}
	return 0;
}

/* Delete an item at the front */
void DeQueue(Queue* pqueue, int lenQue)
{
	if (!IsOne(pqueue, lenQue)) pqueue->front = (pqueue->front + 1) % lenQue;
}

int main()
{
	Queue qu;
	InitQueue(&qu);

	int n, lenQue, i, k = 0;
	char* p, * q;
	p = (char*)malloc(sizeof(char) * 5);
	scanf("%d %d", &n, &lenQue);
	lenQue += 1;
	q = (char*)malloc(sizeof(char) * n);
	for (i = 0; i < n; i++) *(q + i) = 0;
	scanf("%s", qu.items);
	(*&qu).rear = strlen((*&qu).items);
	for (i = 0; i <= n; i++)
	{
		fgets(p, 5, stdin);
		if ('0' == *p) 	*(q + k++) = Peek(&qu);
		else if ('1' == *p) DeQueue(&qu, lenQue);
		else if ('2' == *p)	EnQueue(&qu, *(p + 2), lenQue);
	}
	i = 0;
	while (*(q + i) != 0) printf("%c\n", *(q + i++));
	free(p);
	free(q);
}