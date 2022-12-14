#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node {
	int key;
	int quantity;
	struct _Node* left_child;
	struct _Node* right_child;
} BSTNode;

void CreateLeftSubtree(BSTNode* cur, int key, int quantity) {
	BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
	new_node->key = key;
	new_node->quantity = quantity;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	cur->left_child = new_node;
}
void CreateRightSubtree(BSTNode* cur, int key, int quantity) {
	BSTNode* new_node = (BSTNode*)malloc(sizeof(BSTNode));
	new_node->key = key;
	new_node->quantity = quantity;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	cur->right_child = new_node;
}
/*
void Remove(BSTNode* root, Key key) {
	BSTNode* cur = root, * parent = NULL;
	// Find the current node and its parent node.
	while (cur != NULL && cur->key != key) {
		parent = cur; // Update the parent node.
		if (cur->key > key) cur = cur->left_child;
		else cur = cur->right_child;
	}
	if (cur == NULL) exit(1);
	if (cur->left_child == NULL && cur->right_child == NULL) {
		if (parent != NULL) {
			// Remove the current node depending on its position.
			if (parent->left_child == cur)
				parent->left_child = NULL;
			else parent->right_child = NULL;
		}
		else cur = NULL; // The current node is the root.
	}
	else if (cur->left_child == NULL || cur->right_child == NULL) {
		BSTNode* child;
		// Replace a node with its child node.
		if (cur->left_child != NULL)
			child = cur->left_child;
		else child = cur->right_child;

		// Replace the child node of its parent node.
		if (parent != NULL) {
			if (parent->left_child == cur)
				parent->left_child = child;
			else parent->right_child = child;
		}
	}
	else {
		BSTNode* succ_parent = cur, * succ = cur->right_child;
		// Find the successor (left-most node of the current node.)
		while (succ->left_child != NULL) {
			succ_parent = succ;
			succ = succ->left_child;
		}
		// If the successor has a child, update its the child node.
		if (succ_parent->right_child == succ)
			succ_parent->right_child = succ->right_child;
		else succ_parent->left_child = succ->right_child;

		cur->key = succ->key;
		cur = succ; // remove the seccessor.
	}
	free(cur);
}
*/
void Inorder(BSTNode* root) {
	if (root != NULL) {
		Inorder(root->left_child);
		printf("%d %d\n", root->key, root->quantity);
		Inorder(root->right_child);
	}
}
void Remove(BSTNode* root, int key, int quantity, int* total) {
	BSTNode* cur = root, * parent = NULL;
	// Find the current node and its parent node.
	while (cur != NULL && cur->key != key) {
		parent = cur; // Update the parent node.
		if (cur->key > key) cur = cur->left_child;
		else cur = cur->right_child;
	}
	if (cur == NULL) return;
	if (cur->quantity > quantity) {
		*total -= quantity;
		cur->quantity -= quantity;
		//Inorder(root);
		return;
	}

	if (cur == root) {
		if (cur->quantity > quantity) {
			*total -= quantity;
			cur->quantity -= quantity;
			//Inorder(root);
			return;
		}
		else {
			*total -= cur->quantity;
			cur->quantity = 0;
			//Inorder(root);
			return;
		}
	}
	*total -= cur->quantity;
	if (cur->left_child == NULL && cur->right_child == NULL) {
		if (parent != NULL) {
			// Remove the current node depending on its position.
			if (parent->left_child == cur)
				parent->left_child = NULL;
			else parent->right_child = NULL;
		}
		else cur = NULL; // The current node is the root.
	}
	else if (cur->left_child == NULL || cur->right_child == NULL) {
		BSTNode* child;
		// Replace a node with its child node.
		if (cur->left_child != NULL)
			child = cur->left_child;
		else child = cur->right_child;

		// Replace the child node of its parent node.
		if (parent != NULL) {
			if (parent->left_child == cur)
				parent->left_child = child;
			else parent->right_child = child;
		}
	}
	else {
		BSTNode* succ_parent = cur, * succ = cur->right_child;
		// Find the successor (left-most node of the current node.)
		while (succ->left_child != NULL) {
			succ_parent = succ;
			succ = succ->left_child;
		}
		// If the successor has a child, update its the child node.
		if (succ_parent->right_child == succ)
			succ_parent->right_child = succ->right_child;
		else succ_parent->left_child = succ->right_child;

		cur->key = succ->key;
		cur = succ; // remove the seccessor.
	}
	free(cur);
	Inorder(root);
}

void Insert(BSTNode* Node, int key, int quantity) {
	BSTNode* cur = Node;
	while (cur != NULL) {
		if (cur->key == key) {
			cur->quantity += quantity;
			//Inorder(Node);
			return;
		}
		else if (cur->key > key) {
			if (cur->left_child == NULL) {
				CreateLeftSubtree(cur, key, quantity);
				break;
			}
			else cur = cur->left_child;
		}
		else {
			if (cur->right_child == NULL) {
				CreateRightSubtree(cur, key, quantity);
				break;
			}
			else cur = cur->right_child;
		}
	}
	//Inorder(Node);
}
void Delete(BSTNode* Node, int key, int quantity, int* total) {
	BSTNode* cur = Node;
	while (cur != NULL) {
		if (cur->key == key) {
			if (cur->quantity) {
				if (cur->quantity > quantity) {
					*total -= quantity;
					cur->quantity -= quantity;
				} else {
					*total -= cur->quantity;
					cur->quantity = 0;
				}
			}
			return;
		}
		else if (cur->key > key) cur = cur->left_child;
		else cur = cur->right_child;
	}
}
void Count(BSTNode* Node, int key) {
	BSTNode* cur = Node;
	while (cur) {
		if (cur->key == key) {
			printf("%d\n", cur->quantity);
			return;
		}
		else if (cur->key > key) cur = cur->left_child;
		else cur = cur->right_child;
	}
	printf("%d\n", 0);
	//Inorder(Node);
}
void RangeCount(BSTNode* Node, int min, int max, int* num) {
	BSTNode* cur = Node;
	if (cur == NULL) return;
	if (cur->key > min) RangeCount(cur->left_child, min, max, num);
	if (cur->key >= min && cur->key <= max) *num += cur->quantity;
	if (cur->key < max) RangeCount(cur->right_child, min, max, num);
	//Inorder(Node);
}
void Top(BSTNode* Node, int* n) {
	if (Node->left_child) Top(Node->left_child, n);
	if (*n <= 0) return;
	*n -= Node->quantity;
	if (*n <= 0) {
		printf("%d\n", Node->key);
		return;
	}
	if (Node->right_child) Top(Node->right_child, n);
	//Inorder(Node);
}

int main() {
	BSTNode Node;
	int N, n, m, count = 0, total = 0;
	char fc;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		getchar();
		fc = getchar();

		if (fc == 'I' || fc == 'D' || fc == 'R') scanf("%d %d", &n, &m);
		else scanf("%d", &n);

		if ('I' == fc) {
			total += m;
			if (count) Insert(&Node, n, m);
			else {
				Node.key = n;
				Node.quantity = m;
				Node.left_child = NULL;
				Node.right_child = NULL;
				count++;
			}
		}
		else if ('D' == fc) {
			Remove(&Node, n, m, &total);
		}
		else if ('C' == fc) Count(&Node, n);
		else if ('R' == fc) {
			int num = 0;
			RangeCount(&Node, n, m, &num);
			printf("%d\n", num);
		}
		else {
			if (total < n) printf("-1\n");
			else Top(&Node, &n);
		}
		//printf("total: %d\n", total);
	}
	return 0;
}