#pragma once

#define MAX_QUEUE 100

typedef int Data;
typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
} Queue;

void InitQueue(Queue* pqueue);
bool IsFull(Queue* pqueue);
bool IsQEmpty(Queue* pqueue);
Data QPeek(Queue* pqueue);
void EnQueue(Queue* pqueue, Data item);
void DeQueue(Queue* pqueue);