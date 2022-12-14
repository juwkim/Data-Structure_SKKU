#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _Node {
	int pos;
	int bright;
	int num;
	struct _Node* pre;
	struct _Node* next;
	struct _Node* p_node;
	struct _Node* b_node;
} Node;

typedef struct {
	Node* head;
	int len;
} LinkedList;

// Make a list empty.
void InitList(LinkedList* plist) {
	// Create a dummy node;
	plist->len = 0;
	plist->head = (Node*)malloc(sizeof(Node));
	if (plist->head) plist->head->next = NULL;
	else printf("IiniList 함수에서 메모리를 정상적으로 할당하지 못했습니다.\n");
}

void linktwoList(LinkedList* list_pos, LinkedList* list_bright) {
	Node* cur_p, * cur_b;
	cur_p = list_pos->head->next;
	cur_b = list_bright->head->next;

	// 두 리스트의 노드의 개수가 같기 때문에 cur_p만 체크해도 된다.
	while (cur_p) {
		cur_p->b_node = cur_b;
		cur_b->p_node = cur_p;
		cur_p = cur_p->next;
		cur_b = cur_b->next;
	}
}

void Insert(LinkedList* list, int pos, int bright, int num) {
	Node* cur, * newNode;
	// Create a new node.
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->pos = pos;
		newNode->bright = bright;
		newNode->num = num;
		newNode->next = NULL;

		cur = list->head;

		newNode->next = cur->next;
		newNode->pre = cur;
		cur->next = newNode;
		if (newNode->next) newNode->next->pre = newNode;

		list->len++;
	}
	else printf("Insert 함수에서 메모리를 정상적으로 할당하지 못했습니다.\n");
}

// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next) printf("11 %d ", cur->pos);
}

Node* findcur(LinkedList* list) {
	Node* cur = list->head;
	while (cur->next) cur = cur->next;
	return cur;
}

/*
void check(LinkedList* list_brightNess, LinkedList* list_loc) {
	Node* bcur, * lcur, * tcur;
	int min, max;
	bcur = list_brightNess->head;

	while (bcur->next) {
		bcur = bcur->next;
		min = bcur->loc - bcur->brightNess;
		max = bcur->loc + bcur->brightNess;
		lcur = findmincur(list_loc, min);
		while (lcur->next && lcur->next->loc < max) {
			if (min < lcur->next->loc - lcur->next->brightNess && lcur->next->loc + lcur->next->brightNess <= max) {
				tcur = findcur(list_brightNess, lcur->next->brightNess);
				tcur->next = tcur->next->next;
				lcur->next = lcur->next->next;
				list_loc->len--;
			}
			else if (min <= lcur->next->loc - lcur->next->brightNess && lcur->next->loc + lcur->next->brightNess < max) {
				tcur = findcur(list_brightNess, lcur->next->brightNess);
				tcur->next = tcur->next->next;
				lcur->next = lcur->next->next;
				list_loc->len--;
			}
			else lcur = lcur->next;
		}
	}
}
*/

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
/*
void swap(Node** node1, Node** node2) {

	Node* temp1 = (*node1)->pre;
	Node* temp2 = (*node1)->next;
	printf("here1\n");
	(*node1)->pre = (*node2)->pre;
	printf("here2\n");
	(*node1)->next = (*node2)->next;
	//printf("here3 %d\n", (*node1)->pre->pos);
	((*node1)->pre)->next = *node1;
	printf("here4\n");
	if ((*node2)->next) {
		printf("here5\n");
		(*node1)->next->pre = *node1;
	}
	printf("here6\n");
	(*node2)->pre = temp1;
	printf("here7\n");
	(*node2)->next = temp2;
	printf("here8\n");
	(*node2)->pre->next = *node2;
	printf("here9\n");
	if (temp2) {
		(*node2)->next->pre = *node2;
		printf("here10\n");
	}
	printf("here11\n");
}
*/
Node* Partition(LinkedList* list, Node* left, Node* right, int flag) {
	// 내림차순 정렬;
	int pivot, hpos, lpos, count = 0;
	Node* low = left->next, *high = right;
	if (flag) {
		pivot = left->pos;
		lpos = low->pos;
		hpos = high->pos;
		while (1) {
			printf("here1\n");
			printf("lpos: %d\n", lpos);
			if (count) {
				while (lpos < pivot) {
					high = high->next;
					lpos = high->pos;
					printf("here2\n");
				}
				// Move low until pivot <= (Road + low)->pos
				while (hpos >= pivot) {
					low = low->pre;
					hpos = low->pos;
					printf("here3\n");
				}
			}
			else {
				while (lpos < pivot) {
					low = low->next;
					lpos = low->pos;
					printf("here2\n");
				}
				// Move low until pivot <= (Road + low)->pos
				while (hpos >= pivot) {
					high = high->pre;
					hpos = high->pos;
					printf("here3\n");
				}
			}
			// Move high until pivot > (Road + high)->pos
			printf("here4\n");
			if ((!(count) && lpos > hpos) || (count && lpos < hpos)) {
				printf("here5\n");
				Node* temp1 = low->pre;
				Node* temp2 = low->next;

				low->pre = high->pre;
				low->next = high->next;
				high->pre->next = low;
				if (high->next) high->next->pre = low;

				high->pre = temp1;
				high->next = temp2;
				temp1->next = high;
				if (temp2) temp2->pre = high;
				printf("here6\n");
				count = 1;
				swap(&lpos, &hpos);
			}
			else break;
		}
	}
	else {
		pivot = left->bright;
		while (1) {
			while (low->bright < pivot)
				low = low->next;
			// Move low until pivot <= (Road + low)->pos
			while (high->bright >= pivot)
				high = high->pre;
			// Move high until pivot > (Road + high)->pos
			if (low->bright > high->bright) {
				printf("here5\n");
				Node* temp1 = low->pre;
				Node* temp2 = low->next;

				low->pre = high->pre;
				low->next = high->next;
				high->pre->next = low;
				if (high->next) high->next->pre = low;

				high->pre = temp1;
				high->next = temp2;
				temp1->next = high;
				if (temp2) temp2->pre = high;
				printf("here6\n");
			}
			else break;
		}
	}
	printf("here7\n");
	printf("here5\n");
	Node* temp1 = low->pre;
	Node* temp2 = low->next;

	left->pre = high->pre;
	left->next = high->next;
	high->pre->next = left;
	if (high->next) high->next->pre = left;

	high->pre = temp1;
	high->next = temp2;
	temp1->next = high;
	if (temp2) temp2->pre = high;
	printf("here6\n");
	return high; //return the pivot position.
}

// flag == 1이면 pos 정렬, flag == 0 이면 bright 정렬
// left는 첫번째 노드, right는 마지막 노드
void QuickSort(LinkedList* list, Node* left, Node* right, int flag) {
	Node* mid;
	if (flag == 1) {
		// The mid refers to the pivot position.
		mid = Partition(list, left, right, flag);
		printf("mid->pos %d\n", mid->pos);
		return;
		//printf("mid->pos: %d\n", mid->pos);
		// All elements are less than the pivot.
		QuickSort(list, left, mid->pre, flag);
		// All elements are greater than the pivot.
		QuickSort(list, mid->next, right, flag);
	}
	else {
		mid = Partition(list, left, right, flag);
		QuickSort(list, left, mid->pre, flag);
		QuickSort(list, mid->next, right, flag);
	}
}

int main() {
	int N, pos, bright, order;
	scanf_s("%d", &N);

	/*
	Node** hh = (Node**)malloc(sizeof(Node*) * 6);
	for (int i = 0; i < 6; i++) {
		*(hh + i) = (Node*)malloc(sizeof(Node));
		(*(hh + i))->pos = i;
	}
	printf("first %d %d\n", (*hh)->pos, (*(hh + 1))->pos);
	(*(hh))->pre = *(hh + 1);
	(*(hh + 1))->next = *hh;
	(*(hh))->next = *(hh + 2);
	(*(hh + 2))->pre = *hh;

	(*(hh+3))->pre = *(hh + 4);
	(*(hh + 4))->next = *(hh + 3);
	(*(hh+3))->next = *(hh + 5);
	(*(hh + 5))->pre = *(hh + 3);
	swap(hh, hh + 1);
	printf("second %d %d\n", (*hh)->pos, (*(hh + 1))->pos);
	*/

	LinkedList* list_pos = (LinkedList *)malloc(sizeof(Node) * N);
	LinkedList* list_bright = (LinkedList*)malloc(sizeof(Node) * N);
	if (list_pos && list_bright) {
		InitList(list_pos);
		InitList(list_bright);

		for (order = 1; order <= N; order++) {
			scanf_s("%d", &pos);
			scanf_s(" %d", &bright);

			Insert(list_pos, pos, bright, order);
			Insert(list_bright, pos, bright, order);
		}

		linktwoList(list_pos, list_bright);

		QuickSort(list_pos, list_pos->head->next, findcur(list_pos), 1);
		//QuickSort(list_bright, list_bright->head->next, findcur(list_bright), 0);
		// check(&list_brightNess, &list_loc);
		printf("%d\n", list_pos->len);
		PrintList(list_pos);
	}
	else printf("main에서 메모리를 정상적으로 할당하지 못했습니다.\n");
	return 0;
}