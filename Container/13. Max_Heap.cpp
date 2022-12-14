#include <stdio.h>
#include <stdlib.h>

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

// Make a heap empty.
void InitHeap(Heap *pheap) {
	pheap->num = 0;
}

// check whether a heap is empty.
bool IsEmpty(Heap *pheap) {
	return pheap->num == 0;
}

// Check whether a heap is full.
bool IsFull(Heap* pheap) {
	return pheap->num == MAX_HEAP;
}

// Get a parent index for a given index.
int GetParent(int idx) {
	return idx / 2;
}

// Get a left child index for a given index.
int GetLChild(int idx) {
	return idx * 2;
}

// Get a right child index for a given index.
int GetRChild(int idx) {
	return idx * 2 + 1;
}

int GetHighPrioityChild(Heap* pheap, int idx) {
	// No child nodes exist.
	if (GetLChild(idx) > pheap->num)
		return 0;
	// Exist a left child only.
	else if (GetLChild(idx) == pheap->num)
		return GetLChild(idx);
	// Choose a child node with the highest priority.
	else {
		int left = GetLChild(idx), right = GetRChild(idx);
		if (pheap->items[left].priority > pheap->items[right].priority)
			return left;
		else
			return right;
	}
}

void Insert(Heap* pheap, Data data, int priority) {
	HNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap)) exit(1);
	// Compare the new node with its parent.
	while (idx > 1) {
		int parent = GetParent(idx);
		if (priority > pheap->items[parent].priority) {
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else break;
	}
	newNode.data = data;
	newNode.priority = priority;

	pheap->items[idx] = newNode;
	pheap->num++;
}

Data Delete(Heap* pheap) {
	Data max = pheap->items[1].data;
	HNode last = pheap->items[pheap->num];
	int parent = 1, child;
	// Compare the root with its child nodes.
	while (child = GetHighPrioityChild(pheap, parent)) {
		if (last.priority < pheap->items[child].priority) {
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else break;
	}
	pheap->items[parent] = last;
	pheap->num--;

	return max;
}