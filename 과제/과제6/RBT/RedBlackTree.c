#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "RedBlackTree.h"
#include "Utility.h"
#pragma warning(disable:4996)

Tree* createRBT() {

	// 새로운 트리와 그 안에 들어갈 빈 노드를 만든다
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	Node* newNIL = (Node*)malloc(sizeof(Node));

	// 빈 노드의 속성을 지정하고, 트리의 빈 노드 영역에 할당한다
	if (newTree && newNIL) {
		newNIL->color = BLACK;
		newTree->NIL = newNIL;
		newTree->root = newTree->NIL;
	}
	else printf("createRBT 함수에서 메모리를 정상적으로 할당하지 못했습니다.\n");

	return newTree;
}

Node* createNode(Tree* RBT, int seat) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode) {
		newNode->color = RED;
		newNode->left = RBT->NIL;
		newNode->right = RBT->NIL;
		newNode->seat = seat;
	}
	else printf("createNode 함수에서 메모리를 정상적으로 할당하지 못했습니다.\n");

	return newNode;
}

Node* grandparent(Node* node) {
	if ((node != NULL) && (node->parent != NULL)) return node->parent->parent;
	else return NULL;
}

Node* uncle(Node* node) {
	Node* g = grandparent(node);

	if (g == NULL) return NULL;
	if (node->parent == g->left) return g->right;
	else return g->left;
}

Node* sibling(Node* node) {
	Node* p = node->parent;

	if (p == NULL) return NULL;
	if (node == p->left) return p->right;
	else return p->left;
}

Node* findSuccessor(Tree* RBT, Node* node) {
	while (node->left != RBT->NIL) node = node->left;
	return node;
}

Node* search(Tree* Inventory, int seat) {
	Node* node = Inventory->root;
	if (Inventory->root == Inventory->NIL) return NULL;
	while (node != Inventory->NIL && node->seat != seat) {
		if (node->seat > seat) node = node->left;
		else node = node->right;
	}

	if (node == Inventory->NIL) node = NULL;
	return node;
}

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

void rb_insert(Tree* RBT, Node* node) {
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
		if (curNode->seat > node->seat) curNode = tempNode->left;
		else curNode = tempNode->right;
	}

	node->parent = tempNode;
	if (tempNode->seat > node->seat) tempNode->left = node;
	else tempNode->right = node;

	treeFixUp(RBT, node);
}

void rb_delete(Tree* RBT, Node* node) {
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

void printTree(Tree* RBT, Node* node) {
	if (node->left != RBT->NIL) printTree(RBT, node->left);

	printf("Reserved seat numbers: %d\n", node->seat);

	if (node->right != RBT->NIL) printTree(RBT, node->right);
}

Tree** createTable(int num, int bookedSeat) {
	Tree** Table = (Tree**)malloc(sizeof(Tree*) * num);

	if (Table) {
		srand((unsigned int)time(NULL));

		for (int i = 0; i < num; i++) {
			Tree* tree = createRBT();

			for (int j = 0; j < bookedSeat; j++) {
				int seat = (rand() % 100) + 1;
				Node* node = createNode(tree, seat);
				rb_insert(tree, node);
			}
			*(Table + i) = tree;
		}
	}
	else printf("createTable 함수에서 메모리를 정상적으로 할당하지 못했습니다.\n");
	
	return Table;
}