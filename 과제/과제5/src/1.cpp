#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <malloc.h>

typedef struct _GNode {
	int id;
	int color;
	struct _GNode* next;
} GNode;

typedef struct {
	int num;
	GNode** heads;
} Graph;

//Create a graph.
void CreateGraph(Graph* pgraph, int num, int* pnum) {
	pgraph->num = num;
	pgraph->heads = (GNode**)malloc(sizeof(GNode*) * num);
	for (int i = 0; i < num; i++) {
		// Make a dummy node.
		pgraph->heads[i] = (GNode*)malloc(sizeof(GNode));
		pgraph->heads[i]->color = *(pnum + i);
		pgraph->heads[i]->next = NULL;
	}
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

void check(Graph* pgraph, int* A, int index) {
	*A = -1;
	int color = pgraph->heads[index]->color;
	GNode* cur = pgraph->heads[index]->next;
	int i = 0, j = 0;
	while (cur != NULL) {
		int c = pgraph->heads[cur->id]->color;
		if (c == color && *(A + cur->id) != -1) {
			*(A + cur->id) = -1;
			check(pgraph, A, cur->id);
		}
		cur = cur->next;
	}
}

int main() {

	int n, m;
	scanf("%d %d\n", &n, &m);

	int len = 5 * n;
	char* str = (char*)malloc(sizeof(char) * len);
	fgets(str, len, stdin);

	int i = 0;
	int* num = (int*)malloc(sizeof(int) * n);
	char* ptr = strtok(str, " ");
	while (ptr != NULL) {
		*(num + i++) = atoi(ptr);
		ptr = strtok(NULL, " ");
	}

	Graph g;
	CreateGraph(&g, n, num);

	int src, dest;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &src, &dest);
		AddEdge(&g, src, dest);
	}

	int* A = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		*(A + i) = i;
	}

	int count = 0;
	for (int i = 0; i < n; i++) {
		if (*(A + i) == i) {
			check(&g, A, i);
			count += 1;
		}
		else continue;
	}
	printf("%d", count);
	free(str);
	free(num);
	free(A);
	return 0;
}