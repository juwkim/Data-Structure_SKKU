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
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->len = 0;
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
	newNode->pos = pos;
	newNode->bright = bright;
	newNode->num = num;
	newNode->next = NULL;

	cur = list->head;
	newNode->next = cur->next;
	newNode->pre = cur;
	newNode->next->pre = newNode;
	cur->next = newNode;

	list->len++;
}

// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next) printf("%d ", cur->num);
}

Node* findmincur(LinkedList* list_loc, int min) {
	Node* cur = list_loc->head;
	while (cur->next->loc <= min) cur = cur->next;
	return cur;
}

Node* findcur(LinkedList* list) {
	Node* cur = list->head;
	while (cur->next) cur = cur->next;
	return cur;
}

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

void swap(Node* node1, Node* node2) {

	Node* temp1, *temp2;

	temp1 = node1->pre;
	temp2 = node1->next;

	node1->pre = node2->pre;
	node1->next = node2->next;
	node1->pre->next = node1;
	node1->next->pre = node1;

	node2->pre = temp1;
	node2->next = temp2;
	temp1->next = node2;
	temp2->pre = node2;
}

Node* Partition(LinkedList* list, Node* left, Node* right, int flag) {
	// 내림차순 정렬;
	int pivot; = left->pos;
	Node* low = left->next, high = right;
	if (flag) {
		pivot = left->pos;
		while (1) {
			while ((low->pos < right->pos) && (low->pos < pivot))
				low = low->next;
			// Move low until pivot <= (Road + low)->pos
			while ((high->pos > left->pos) && (high->pos >= pivot))
				high = high->pre;
			// Move high until pivot > (Road + high)->pos
			if (low->pos < high->pos)
				// Swap Road[low] and Road[high].
				swap(low, high);
			else break;
		}
	}
	else {
		pivot = left->bright;
		while (1) {
			while ((low->bright < right->bright) && (low->bright < pivot))
				low = low->next;
			// Move low until pivot <= (Road + low)->pos
			while ((high->bright > left->bright) && (high->bright >= pivot))
				high = high->pre;
			// Move high until pivot > (Road + high)->pos
			if (low->bright < high->bright)
				// Swap Road[low] and Road[high].
				swap(low, high);
			else break;
		}
	}
	swap(left, high);
	return high; //return the pivot position.
}

// flag == 1이면 pos 정렬, flag == 0 이면 bright 정렬
// left는 첫번째 노드, right는 마지막 노드
void QuickSort(LinkedList* list, Node* left, Node* right, int flag) {
	Node* mid;
	if ((flag == 1) && (left->pos < right->pos)) {
		// The mid refers to the pivot position.
		mid = Partition(list, left, right, flag);
		// All elements are less than the pivot.
		QuickSort(Road, left, mid->pre, flag);
		// All elements are greater than the pivot.
		QuickSort(Road, mid->next, right, flag);
	}
	else if ((flag == 0) && (left->bright < right->bright)) {
			mid = Partition(list, left, right, flag);
			QuickSort(Road, left, mid->pre, flag);
			QuickSort(Road, mid->next, right, flag);
	}
}

int main() {
	int N, pos, bright, order;
	//scanf("%d", &N);

	Node* node1, * node2;
	node1->pos = 1, node2->pos = 2;
	printf("%d %d\n", node1->pos, node2->pos);
	swap(node1, node2);
	printf("%d %d\n", node1->pos, node2->pos);
	/*
	LinkedList* list_pos = (LinkedList *)malloc(sizeof(Node) * N);
	LinkedList* list_bright = (LinkedList*)malloc(sizeof(Node) * N);
	InitList(list_pos);
	InitList(list_bright);

	for (order = 1; order <= N; order++) {
		scanf("%d", &pos);
		scanf(" %d", &bright);

		Insert(list_pos, pos, bright, order);
		Insert(list_bright, pos, bright, order);
	
	linktwoList(list_pos, list_bright);
	QuickSort(list_pos, list_pos->hade->next, findcur(list_pos), 1);
	QuickSort(list_bright, list_bright->hade->next, findcur(list_bright), 0);
	// check(&list_brightNess, &list_loc);
	printf("%d\n", list_pos->len);
	PrintList(&list_pos);
	*/
	return 0;
}