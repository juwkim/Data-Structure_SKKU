#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _GNode {
	int id;
	int patient;
	struct _GNode* next;
} GNode;

typedef struct {
	GNode** heads;
} Graph;

//Create a graph.
void CreateGraph(Graph* pgraph, int num, int* pnum, int x) {
	pgraph->heads = (GNode**)malloc(sizeof(GNode*) * num);
	for (int i = 0; i < num; i++) {
		// Make a dummy node.
		pgraph->heads[i] = (GNode*)malloc(sizeof(GNode));
		pgraph->heads[i]->patient = 0;
		pgraph->heads[i]->next = NULL;
	}
	for (int i = 0; i < x; i++)
		pgraph->heads[*(pnum + i)]->patient = 1;
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

void check(Graph* pgraph, int index, int* count, int step, int* M) {
	GNode* cur = pgraph->heads[index]->next;
	step += 1;
	//printf("index and step: %d %d\n", index, step);
	while (cur != NULL) {
		int c = pgraph->heads[cur->id]->patient;
		if (c == 0) {
			//printf("cur->id: %d\n", cur->id);
			*count += 1;
			pgraph->heads[cur->id]->patient = 1;
		}
		if (step < *M) check(pgraph, cur->id, count, step, M);
		cur = cur->next;
	}
}

int main() {
	int n, M, x, y;
	scanf("%d %d %d %d\n", &n, &M, &x, &y);

	int len = 6 * x;
	char* str = (char*)malloc(sizeof(char) * len);
	fgets(str, len, stdin);

	int i = 0;
	int* num = (int*)malloc(sizeof(int) * x);
	char* ptr = strtok(str, " ");
	while (ptr != NULL) {
		int patient = atoi(ptr);
		*(num + i++) = patient;
		ptr = strtok(NULL, " ");
	}

	Graph g;
	CreateGraph(&g, n, num, x);

	int src, dest;
	for (int i = 0; i < y; i++) {
		scanf("%d %d", &src, &dest);
		AddEdge(&g, src, dest);
	}

	int count = 0, step = 0;
	for (int i = 0; i < x; i++) {
		int index = *(num + i);
		check(&g, index, &count, step, &M);
	}
	printf("%d", count);
	return 0;
}