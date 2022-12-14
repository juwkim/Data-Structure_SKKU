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

Tree *createRBT();										 /* 레드블랙트리 생성 */
Node* createNode(Tree* RBT, int seat);					 /* 새로운 노드 생성 */

Node *grandparent(Node *node);							 /* 노드의 부모의 부모 노드 */
Node *uncle(Node *node);								 /* 노드의 부모의 형제 노드 */
Node *sibling(Node *node);								 /* 노드의 형제 노드 */
Node* findSuccessor(Tree* RBT, Node* node);				 /* Successor 찾기 */
Node* search(Tree* Inventory, int seat);				 /* seat 값을 가진 노드 찾기 */

void rotateLeft(Tree* RBT, Node* node);					 /* 트리 좌측 회전 */
void rotateRight(Tree* RBT, Node* node);				 /* 트리 우측 회전 */
void transPlant(Tree* RBT, Node* node, Node* successor); /* 트리 옮겨 심기 */

void treeFixUp(Tree *RBT, Node *node);					 /* 삽입시 트리 균형 수정 */
void treeDelFixUp(Tree *RBT, Node *node);				 /* 삭제시 트리 균형 수정 */

void rb_insert(Tree* RBT, Node* node);					 /* 트리에 노드 삽입 */
void rb_delete(Tree* RBT, Node* node);					 /* 트리 노드 삭제 */

void printTree(Tree *RBT, Node *node);					 /* 트리 노드 출력 */

Tree** createTable(int num, int bookedSeat);			 /* num개의 Tree에 각각 bookedSeat개의 노드를 삽입한다.*/