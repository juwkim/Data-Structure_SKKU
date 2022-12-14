#pragma once

#define BLACK 1
#define RED 0

typedef struct node {
	int seat;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
} Node;

typedef struct {
	Node *root;
	Node *NIL;
} Tree;

Tree *createRBT();										 /* �����Ʈ�� ���� */
Node* createNode(Tree* RBT, int seat);					 /* ���ο� ��� ���� */

Node *grandparent(Node *node);							 /* ����� �θ��� �θ� ��� */
Node *uncle(Node *node);								 /* ����� �θ��� ���� ��� */
Node *sibling(Node *node);								 /* ����� ���� ��� */
Node* findSuccessor(Tree* RBT, Node* node);				 /* Successor ã�� */
Node* search(Tree* Inventory, int seat);				 /* seat ���� ���� ��� ã�� */

void rotateLeft(Tree* RBT, Node* node);					 /* Ʈ�� ���� ȸ�� */
void rotateRight(Tree* RBT, Node* node);				 /* Ʈ�� ���� ȸ�� */
void transPlant(Tree* RBT, Node* node, Node* successor); /* Ʈ�� �Ű� �ɱ� */

void treeFixUp(Tree *RBT, Node *node);					 /* ���Խ� Ʈ�� ���� ���� */
void treeDelFixUp(Tree *RBT, Node *node);				 /* ������ Ʈ�� ���� ���� */

void rb_insert(Tree* RBT, Node* node);					 /* Ʈ���� ��� ���� */
void rb_delete(Tree* RBT, Node* node);					 /* Ʈ�� ��� ���� */

void printTree(Tree *RBT, Node *node);					 /* Ʈ�� ��� ��� */

Tree** createTable(int num, int bookedSeat);			 /* num���� Tree�� ���� bookedSeat���� ��带 �����Ѵ�.*/