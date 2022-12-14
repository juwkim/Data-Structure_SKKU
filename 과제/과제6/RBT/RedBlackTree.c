#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "RedBlackTree.h"
#include "Utility.h"
#pragma warning(disable:4996)

Tree* createRBT() {

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	Node* newNIL = (Node*)malloc(sizeof(Node));

	// �� ����� �Ӽ��� �����ϰ�, Ʈ���� �� ��� ������ �Ҵ��Ѵ�
	if (newTree && newNIL) {
		newNIL->color = BLACK;
		newTree->NIL = newNIL;
		newTree->root = newTree->NIL;
	}
	else printf("createRBT �Լ����� �޸𸮸� ���������� �Ҵ����� ���߽��ϴ�.\n");

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
	else printf("createNode �Լ����� �޸𸮸� ���������� �Ҵ����� ���߽��ϴ�.\n");

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

	// �θ� ��Ʈ ����� ���
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

	// �θ� ��Ʈ ����� ���
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
	// ��Ʈ����� ���
	if (node->parent == NULL) RBT->root = Successor;

	// ���� ���
	else if (node == node->parent->left) node->parent->left = Successor;

	// ���� ���
	else node->parent->right = Successor;

	Successor->parent = node->parent;
}

void treeFixUp(Tree* RBT, Node* node) {
	Node* p = node->parent;
	Node* u = uncle(node);
	Node* g = grandparent(node);

	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (node == RBT->root) {
		node->color = BLACK;
		return;
	}

	// case2 : ������ ����� �θ� �������� ���
	else if (p->color == BLACK) return;

	// case3 : ������ ���� �θ� ����� ���� �������� ���
	else if (node->color == RED && p->color == RED) {
		// case 3-1 : ���� ��尡 �������� ���
		if (u->color == BLACK) {

			// case 3-1-1 : ���� ���� �θ� ����� ������ �ݴ��� ���
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

			// case 3-1-2 : ���� ���� �θ� ����� ������ ������ ���
			p->color = BLACK;
			g->color = RED;
			if (p == g->left) rotateRight(RBT, p);
			else if (p == g->right) rotateLeft(RBT, p);
		}

		// case 3-2 : ���� ��尡 �������� ���
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

	// case 1 : s->red (sibling ���� ȸ�� -> sibling�� BLACK�� ���·� FixUp)
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

	// ���� ��尡 ��Ʈ����� ���
	if (RBT->root == RBT->NIL) {
		RBT->root = node;
		node->parent = NULL;
		node->color = BLACK;
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
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

	// child 0, 1 : ���ʳ�� ���� ���
	if (left == RBT->NIL) {
		fixupNode = right;
		transPlant(RBT, node, right);
	}

	// child 1 : �����ʳ�� ���� ���
	else if (right == RBT->NIL) {
		fixupNode = left;
		transPlant(RBT, node, left);
	}

	// child 2 : �ڽĳ�� 2���� ��� -> successor�� �����ϴ� ������ ����
	else {
		successor = findSuccessor(RBT, right);
		nColor = successor->color;

		fixupNode = successor->right;

		// fixupNode�� successor�� �ڸ��� �̽�
		transPlant(RBT, successor, fixupNode);
		successor->right = node->right;
		successor->right->parent = successor;

		// successor�� node�� �ڸ��� �̽�
		transPlant(RBT, node, successor);
		successor->left = node->left;
		successor->left->parent = successor;

		successor->color = node->color;
	}

	// ���� ����� ���� BLACK�� ��� Violation �߻�
	if (nColor == BLACK) treeDelFixUp(RBT, fixupNode);

	// �޸� ���� �ع������
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
	else printf("createTable �Լ����� �޸𸮸� ���������� �Ҵ����� ���߽��ϴ�.\n");
	
	return Table;
}