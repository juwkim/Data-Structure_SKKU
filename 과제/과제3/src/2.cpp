#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef int Data;

typedef struct _Node {
	Data add;
	Data size;
	Data dist;
	struct _Node* next;
} Node;

typedef struct {
	Node* head;
	int	len;
} LinkedList;

void InitList(LinkedList* plist, Data L) {
	// Create a dummy node;
	plist->len = 0;
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->dist = L;
	plist->head->next = NULL;
	plist->len = 0;
}

void freem(LinkedList* list, Data add, Data size) {
	Node* head = list->head;
	Node* hh = list->head;
	while (add != head->next->add) head = head->next;
	if (head == hh) {
		Node* temp;
		list->len += (size + head->next->dist);
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	else if (head->next->next != NULL) {
		Node* temp;
		head->dist += (size + head->next->dist);
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	else {
		head->dist += (size + head->next->dist);
		free(head->next);
		head->next = NULL;
	}
}

int alloc(LinkedList* list, Data size, Data L) {
	Node* head = list->head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	Data add = 0;
	if (size > head->dist) {
		free(newNode);
		return -1;
	}
	else if (size == head->dist && head->next != NULL) {
		free(newNode);
		return -1;
	}
	else if (head->next == NULL) {
		head->next = newNode;
		newNode->add = 0;
		newNode->size = size;
		newNode->dist = head->dist - size;
		newNode->next = NULL;
	}
	else if (head->next != NULL) {
		Data sdist = L;
		add = head->next->size; 
		while (head->next != NULL) {
			if (head->next->dist >= size && head->next->dist < sdist) {
				sdist = head->next->dist;
				add = (head->next->add + head->next->size);
			}
			head = head->next;
		}
		if (head->dist < sdist && head->dist >= size) {
			sdist = head->dist;
			add = head->add + head->size;
		}
		if (list->len < sdist && list->len >= size) {
			sdist = list->len;
			add = 0;
			newNode->next = head->next;
			head->next = newNode;
			newNode->add = add;
			newNode->size = size;
			newNode->dist = sdist - size;
			list->len = 0;
			return add;
		}
		if (size > sdist) {
			return -1;
		}
		else if (sdist == L) return -1;
		else {
			Node* cur = list->head->next;
			while (add != (cur->add + cur->size)) cur = cur->next;
			cur->dist = 0;
			if (cur->next != NULL) {
				newNode->next = cur->next;
				cur->next = newNode;
				newNode->add = add;
				newNode->size = size;
				newNode->dist = sdist - size;
			}
			else {
				newNode->next = NULL;
				cur->next = newNode;
				newNode->add = add;
				newNode->size = size;
				newNode->dist = sdist - size;
			}
		}
		printf("sdist & add: %d %d\n", sdist, add);
	}
	return add;
}

int main() {
	LinkedList list;
	Data L, N, size, add;
	int* p;
	int i = 0, j = 0;
	char opr[6] = { 0, };
	scanf("%d %d", &L, &N);

	InitList(&list, L);

	p = (int*)malloc(sizeof(int) * (N + 1));
	for (i = 0; i < N + 1; i++) *(p + i) = -2;

	for (int b = 0; b < N; b++) {

		scanf("%s", opr);
		if ('a' == opr[0]) {
			scanf("%d", &size);
			*(p + j) = alloc(&list, size, L);
			j++;
		}

		else {
			scanf("%d %d", &add, &size);
			freem(&list, add, size);
		}
	}
	i = 0;
	while (*(p + i) != -2) {
		printf("%d\n", *(p + i));
		i++;
	}
	free(p);
	return 0;
}