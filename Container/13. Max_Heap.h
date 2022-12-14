#pragma once

#define MAX_HEAP 100

typedef char Data;
typedef struct {
	Data data;
	int priority;
} HNode;

typedef struct {
	HNode items[MAX_HEAP + 1];
	int num;
} Heap;

void InitHeap(Heap* pheap);
// check whether a heap is empty.
bool IsEmpty(Heap* pheap);

// Check whether a heap is full.
bool IsFull(Heap* pheap);

// Get a parent index for a given index.
int GetParent(int idx);

// Get a left child index for a given index.
int GetLChild(int idx);

// Get a right child index for a given index.
int GetRChild(int idx);

int GetHighPrioityChild(Heap* pheap, int idx);

void Insert(Heap* pheap, Data data, int priority);

Data Delete(Heap* pheap);