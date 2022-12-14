#include <stdio.h>
#include <malloc.h>
#include "stack.h"
#include "Queue.h"

typedef struct _GNode {
	int id;
	struct _GNode* next;
} GNode;

typedef struct {
	int num;
	GNode** heads;
} Graph;

// Create a graph.
void CreateGraph(Graph* pgraph, int num) {
	pgraph->num = num;
	pgraph->heads = (GNode**)malloc(sizeof(GNode*) * num);
	for (int i = 0; i < num; i++) {
		// Make a dummy node.
		pgraph->heads[i] = (GNode*)malloc(sizeof(GNode));
		pgraph->heads[i]->next = NULL;
	}
}

// Destroy a graph.
void DestroyGraph(Graph* pgraph) {
	for (int i = 0; i < pgraph->num; i++) {
		GNode* cur = pgraph->heads[i];
		while (cur != NULL) {
			GNode* temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(pgraph->heads);
}

// Add an undirected edge from src to dest.
void AddEdge(Graph* pgraph, int src, int dest) {
	GNode* newNode1, * newNode2, * cur;

	newNode1 = (GNode*)malloc(sizeof(GNode));
	newNode1->id = dest;
	newNode1->next = NULL;

	// Create a node for dest in src.
	cur = pgraph->heads[src]; 
	while (cur->next != NULL) // unsorted
		cur = cur->next; // parallel edges
	cur->next = newNode1;

	newNode2 = (GNode*)malloc(sizeof(GNode));
	newNode2->id = src;
	newNode2->next = NULL;
	
	// Create a node for src in dest.
	cur = pgraph->heads[dest];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode2;
}

// Print a graph for each vertex.
// void PrintGraph(Graph* pgraph);

// Depth first search
void DFS(Graph* pgraph) {
	Stack stack;
	bool* visited = (bool*)malloc(sizeof(bool) * pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		// Make all vertices unvisited.
		visited[i] = false;

	InitStack(&stack);
	// Push the initial vertex.
	Push(&stack, 0);

	while (!IsEmpty(&stack)) {
		GNode* cur;
		int vtx = Peek(&stack);
		Pop(&stack);

		// Skip if the vertex has been visited.
		if (visited[vtx]) continue;
		else {
			visited[vtx] = true;
			printf("%d ", vtx);
		}

		// Push the vertex if it has not been visited.
		cur = pgraph->heads[vtx]->next;
		while (cur != NULL) {
			if (!visited[cur->id])
				Push(&stack, cur->id);
			cur = cur->next;
		}
	}
}
		
// Breadth first search
void BFS(Graph* pgraph) {
	Queue queue;
	bool* visited = (bool*)malloc(sizeof(bool) * pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		// Make all vertices unvisited.
		visited[i] = false;

	InitQueue(&queue);
	// Enqueue the initial vertex.
	EnQueue(&queue, 0);
	while (!IsQEmpty(&queue)) {
		GNode* cur;
		int vtx = QPeek(&queue);
		DeQueue(&queue);

		// Skip if the vertex has been visited.
		if (visited[vtx]) continue;
		else {
			visited[vtx] = true;
			printf("%d ", vtx);
		}

		// Enqueue the vertex if it has been unvisited.
		cur = pgraph->heads[vtx]->next;
		while (cur != NULL) {
			if (!visited[cur->id])
				EnQueue(&queue, cur->id);
			cur = cur->next;
		}
	}
}