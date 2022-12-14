#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#define BLACK 1
#define RED 0

typedef struct node {
	int color;
	int grade;
	int quantity;
	struct node* parent;
	struct node* left;
	struct node* right;
} Node;
typedef struct {
	Node* root;
	Node* NIL;
} Tree;

// 레드블랙트리 생성
Tree* createRBT(void) {

	// 새로운 트리와 그 안에 들어갈 빈 노드를 만든다
	Tree* newTree = (Tree *)malloc(sizeof(Tree));
	Node* newNIL = (Node *)malloc(sizeof(Node));

	// 빈 노드의 속성을 지정하고, 트리의 빈 노드 영역에 할당한다
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

// 노드 생성
Node* createNode (Tree* RBT, int grade, int quantity) {
	Node* newMember = (Node *)malloc(sizeof(Node));

	newMember->color = RED;
	newMember->left = RBT->NIL;
	newMember->right = RBT->NIL;
	newMember->grade = grade;
	newMember->quantity = quantity;

	return newMember;
}

// 현재 노드의 부모의 부모 노드
Node* grandparent(Node* node) {
	if ((node != NULL) && (node->parent != NULL)) return node->parent->parent;
	else return NULL;
}

// 현재 노드의 부모의 형제 노드
Node* uncle(Node* node) {
	Node* g = grandparent(node);

	if (g == NULL) return NULL;
	if (node->parent == g->left) return g->right;
	else return g->left;
}

// 현재 노드의 형제 노드
Node* sibling(Node* node) {
	Node* p = node->parent;

	if (p == NULL) return NULL;
	if (node == p->left) return p->right;
	else return p->left;
}

// 노드와 부모 노드의 위치를 왼쪽으로 돌림
void rotateLeft(Tree* RBT, Node* node) {
	Node* p = node->parent;
	Node* g = grandparent(node);
	Node* temp = node->left;

	// 부모가 루트 노드인 경우
	if (g == NULL) RBT->root = node;
	else if (p == g->left) g->left = node;
	else g->right = node;

	node->parent = g;
	node->left = p;
	p->parent = node;
	p->right = temp;
	temp->parent = p;
}

// 노드와 부모 노드의 위치를 오른쪽으로 돌림
void rotateRight(Tree* RBT, Node* node) {
	Node* p = node->parent;
	Node* g = grandparent(node);
	Node* temp = node->right;

	// 부모가 루트 노드인 경우
	if (g == NULL) RBT->root = node;
	else if (p == g->left) g->left = node;
	else g->right = node;

	node->parent = g;
	node->right = p;
	p->parent = node;
	p->left = temp;
	temp->parent = p;
}

// Successor 찾기
Node* findSuccessor(Tree* RBT, Node* node) {
	while (node->left != RBT->NIL) node = node->left;
	return node;
}

void transPlant(Tree* RBT, Node* node, Node* Successor) {
	// 루트노드인 경우
	if (node->parent == NULL) RBT->root = Successor;

	// 좌측 노드
	else if (node == node->parent->left) node->parent->left = Successor;

	// 우측 노드
	else node->parent->right = Successor;

	Successor->parent = node->parent;
}

void treeFixUp(Tree* RBT, Node* node) {
	Node* p = node->parent;
	Node* u = uncle(node);
	Node* g = grandparent(node);

	// case1 : 삽입한 노드가 루트 노드인 경우
	if (node == RBT->root) {
		node->color = BLACK;
		return;
	}

	// case2 : 삽입한 노드의 부모가 검은색인 경우
	else if (p->color == BLACK) return;

	// case3 : 삽입한 노드와 부모 노드의 색이 빨간색인 경우
	else if (node->color == RED && p->color == RED) {
		// case 3-1 : 삼촌 노드가 검은색인 경우
		if (u->color == BLACK) {

			// case 3-1-1 : 현재 노드와 부모 노드의 방향이 반대인 경우
			if (node == p->left && p == g->right) {
				rotateRight(RBT, node);
				node = p;
			}
			else if (node == p->right && p == g->left) {
				rotateLeft(RBT, node);
				node = p;
			}

			p = node->parent;
			u = uncle(node);
			g = grandparent(node);

			// case 3-1-2 : 현재 노드와 부모 노드의 방향이 직선인 경우
			p->color = BLACK;
			g->color = RED;
			if (p == g->left) rotateRight(RBT, p);
			else if (p == g->right) rotateLeft(RBT, p);
		}

		// case 3-2 : 삼촌 노드가 빨간색인 경우
		else {
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			treeFixUp(RBT, g);
		}
	}
}

// 새로운 노드 삽입
void insertNode(Tree* RBT, Node* node) {
	Node* curNode, * tempNode;

	// 현재 노드가 루트노드일 경우
	if (RBT->root == RBT->NIL) {
		RBT->root = node;
		node->parent = NULL;
		node->color = BLACK;
		return;
	}

	// 현재 노드가 들어갈 위치를 찾아 NIL노드와 교체
	curNode = RBT->root;
	tempNode = curNode;

	while (curNode != RBT->NIL) {
		tempNode = curNode;
		if (curNode->grade > node->grade) curNode = tempNode->left;
		else curNode = tempNode->right;
	}

	node->parent = tempNode;
	if (tempNode->grade > node->grade) tempNode->left = node;
	else tempNode->right = node;

	treeFixUp(RBT, node);
}

void treeDelFixUp(Tree* RBT, Node* node) {
	Node* p = node->parent;
	Node* s = sibling(node);

	// case 1 : s->red (sibling 기준 회전 -> sibling이 BLACK인 상태로 FixUp)
	if (s->color == RED) {
		p->color = RED;
		s->color = BLACK;
		if (node == p->left) rotateLeft(RBT, s);
		else rotateRight(RBT, s);
		treeDelFixUp(RBT, node);
	}

	else {
		// case 2 : left->black, right->black
		if (s->left->color == BLACK && s->right->color == BLACK) {
			s->color = RED;
			if (p->color == RED) p->color = BLACK;
			else treeDelFixUp(RBT, p);
		}

		else {
			if (node == p->left) {
				// case 3 : left->red, right->black
				if (s->right->color == BLACK) {
					s->left->color = BLACK;
					s->color = RED;
					rotateRight(RBT, s->left);
					s = sibling(node);
				}

				// case 4 : left->black/red, right->red
				s->color = p->color;
				p->color = BLACK;
				s->right->color = BLACK;
				rotateLeft(RBT, s);
			}
			else {
				// case 3-2 : left->black, right->red
				if (s->left->color == BLACK) {
					s->right->color = BLACK;
					s->color = RED;
					rotateLeft(RBT, s->right);
					s = sibling(node);
				}

				// case 4-2 : left->red, right->black/red
				s->color = p->color;
				p->color = BLACK;
				s->left->color = BLACK;
				rotateRight(RBT, s);
			}
		}
	}
}

// 트리 노드 삭제 
void removeNode(Tree* RBT, Node* node) {
	Node* successor, * fixupNode;
	Node* left = node->left;
	Node* right = node->right;
	Node* p = node->parent;
	int nColor = node->color;

	// child 0, 1 : 왼쪽노드 없는 경우
	if (left == RBT->NIL) {
		fixupNode = right;
		transPlant(RBT, node, right);
	}

	// child 1 : 오른쪽노드 없는 경우
	else if (right == RBT->NIL) {
		fixupNode = left;
		transPlant(RBT, node, left);
	}

	// child 2 : 자식노드 2개인 경우 -> successor를 삭제하는 것으로 가정
	else {
		successor = findSuccessor(RBT, right);
		nColor = successor->color;

		fixupNode = successor->right;

		// fixupNode를 successor의 자리에 이식
		transPlant(RBT, successor, fixupNode);
		successor->right = node->right;
		successor->right->parent = successor;

		// successor를 node의 자리에 이식
		transPlant(RBT, node, successor);
		successor->left = node->left;
		successor->left->parent = successor;

		successor->color = node->color;
	}

	// 삭제 노드의 색이 BLACK인 경우 Violation 발생
	if (nColor == BLACK) treeDelFixUp(RBT, fixupNode);

	// 메모리 영역 해방시켜줌
	free(node);
}

// 트리 출력
void printTree(Tree* RBT, Node* node) {
	if (node->left != RBT->NIL) printTree(RBT, node->left);

	printf("Diamond grade and quantity: %d %d\n", node->grade, node->quantity);
	
	if (node->right != RBT->NIL) printTree(RBT, node->right);
}

// 트리 검색
Node* search(Tree* Inventory, int grade) {
	Node* node = Inventory->root;
	if (Inventory->root == Inventory->NIL) return NULL;
	while (node != Inventory->NIL && node->grade != grade) {
		if (node->grade > grade) node = node->left;
		else node = node->right;
	}

	if (node == Inventory->NIL) node = NULL;
	return node;
}

void Insert(Tree* Inventory, int grade, int quantity, int* total) {
	Node* checkExistence = search(Inventory, grade);
	if (checkExistence) checkExistence->quantity += quantity;
	else {
		Node* newMember = createNode(Inventory, grade, quantity);
		insertNode(Inventory, newMember);
	}
	*total += quantity;
}
void Delete(Tree* Inventory, int grade, int quantity, int* total) {
	Node* deleteNode = search(Inventory, grade);
	if (deleteNode) {
		if (deleteNode->quantity > quantity) {
			deleteNode->quantity -= quantity;
			*total -= quantity;
		} else {
			*total -= deleteNode->quantity;
			removeNode(Inventory, deleteNode);
		}
	}
}
void Count(Tree* Inventory, int grade) {
	Node* countNode = search(Inventory, grade);
	if (countNode) printf("%d\n", countNode->quantity);
	else printf("%d\n", 0);
}
void RangeCount(Tree* Inventory, Node* node, int min, int max, int* total_quantity) {
	if (Inventory->root == Inventory->NIL) return;
	if (node->left != Inventory->NIL && node->grade > min) RangeCount(Inventory, node->left, min, max, total_quantity);
	if (min <= node->grade && node->grade <= max) *total_quantity += node->quantity;
	if (node->right != Inventory->NIL && node->grade < max) RangeCount(Inventory, node->right, min, max, total_quantity);
}
void Top(Tree* Inventory, Node* node, int* order) {

	if (node->left != Inventory->NIL) Top(Inventory, node->left, order);

	if (*order <= 0) return;
	*order -= node->quantity;
	if (*order <= 0) {
		printf("%d\n", node->grade);
		return;
	}

	if (node->right != Inventory->NIL) Top(Inventory, node->right, order);
}
int max(int a, int b) {
	if (a >= b) return a;
	else return b;
}
int min(int a, int b) {
	if (a >= b) return b;
	else return a;
}

int main() {
	Tree* Inventory = createRBT();
	int N, n, m = 0, total = 0;
	char function;

	scanf("%d", &N);
	//N = 100000;
	//srand(time(NULL));
	//printf("%d만큼 반복 시작합니다.^^\n", N);

	/*
	clock_t start, end;
	double result;
	start = clock();
	*/
	for (int i = 0; i < N; i++) {
		/*
		//_sleep(2000);
		int function = rand() % 5;
		n = (rand() % 10000000) + 1;
		m = (rand() % 1000) + 1;
		//printf("%d 번째 실행입니다.\n", i);
		//printf("function n and m %d %d %d^^\n", function, n, m);
		if (0 == function) Insert(Inventory, n, m, &total);
		else if (1 == function) Delete(Inventory, n, m, &total);
		else if (2 == function) Count(Inventory, n);
		else if (3 == function) {
			m = (rand() % 10000000) + 1;
			int total_quantity = 0;
			RangeCount(Inventory, Inventory->root, min(n, m), max(n, m), &total_quantity);
			printf("%d\n", total_quantity);
		}
		else if (total < n) printf("-1\n");
		else Top(Inventory, Inventory->root, &n);
		//printf("function n and m %d %d %d^^\n", function, n, m);
		//printTree(Inventory, Inventory->root);
		*/
		
		getchar();
		function = getchar();

		if ('I' == function || 'D' == function || 'R' == function) scanf("%d %d", &n, &m);
		else scanf("%d", &n);

		if ('I' == function) Insert(Inventory, n, m, &total);
		else if ('D' == function) Delete(Inventory, n, m, &total);
		else if ('C' == function) Count(Inventory, n);
		else if ('R' == function) {
			int total_quantity = 0;
			RangeCount(Inventory, Inventory->root, n, m, &total_quantity);
			printf("%d\n", total_quantity);
		}
		else if (total < n) printf("-1\n");
		else Top(Inventory, Inventory->root, &n);
		printTree(Inventory, Inventory->root);
		
	
	}
	//end = clock(); //시간 측정 끝
	//result = (double)(end - start);
	//printf("time: %f", result);
	return 0;
}