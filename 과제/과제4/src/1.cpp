# include <stdio.h>
# include <malloc.h>

typedef int BData;
typedef struct _bTreeNode {
	BData item;
	struct _bTreeNode* left_child;
	struct _bTreeNode* right_child;
} BTreeNode;

// Create a new node.
BTreeNode* CreateNode(BData item) {
	BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
	node->item = item;
	node->left_child = NULL;
	node->right_child = NULL;

	return node;
}

// LRC ������ Binary Tree�� ����Ѵ�.
void Postorder(BTreeNode* root) {
	if (root != NULL) {
		Postorder(root->left_child);
		Postorder(root->right_child);
		printf("%d ", root->item);
	}
}

// �������� ���е� ���� �Է��� str�� �޾Ƽ�
// int �������� ��ȯ�Ͽ� ������ int*�� ��ȯ�Ѵ�.
int* StrToNum(char* str, int max_count) {
	// ���ڿ����� �и��� ������ ������ ������ ����(count)
	// ���ڿ����� �и��� ������ �ӽ÷� ������ ����(num)
	int count = 0, num = 0;
	// ���ڿ����� �и��� ������ ������ ������ �Ҵ��Ѵ�.
	int* pnum = (int*)malloc(sizeof(int) * max_count);

	while (count < max_count && *str) {
		if (*str != ' ') {
			// ���� ���ڰ� �ƴ� ���, ���ڸ� ���ڷ� �����Ѵ�.
			num = num * 10 + *str - '0';
		}
		else {
			// ���� ���ڶ�� num�� ���� ������ �Ϸ�� ���̹Ƿ�,
			// num�� pnum�� �߰��Ѵ�.
			if (num > 0) {
				*(pnum + count++) = num;
				num = 0;
			}
		}
		str += 1;
	}
	// ������ ���� �ڿ��� ������ �����Ƿ�, ������ ���ڴ� ������ ������ ���� �ʴ´�.
	// ���� ������ ���ڵ� pnum�� �����Ѵ�.
	if (num > 0) *(pnum + count++) = num;

	return pnum;
}

// Pint���� value�� ã�� �Լ�
int Search(int* Pint, int value, int start, int end) {
	for (int i = start; i <= end; i++)
		if (value == *(Pint + i)) return i;
	return -1;
}

BTreeNode* MakeTree(int* preorder, int* inorder, int instart, int inend) {

	// preindex�� �����Ѵ�. �� �� �Լ� ȣ�� ������ 0���� �ʱ�ȭ ���� �ʰ�
	// static�� ���� �տ� ����.
	static int preindex = 0;

	// inindex�� instart �Ǵ� inend�� ���ٴ� �ǹ��̴�.
	// ��尡 ���ٴ� �ǹ��̹Ƿ�, NULL�� ��ȯ�Ѵ�.
	if (instart > inend) return NULL;

	else {
		BTreeNode* node = CreateNode(*(preorder + preindex++));

		// �ڽ� ��尡 ���ٴ� �ǹ��̹Ƿ�, node�� ��ȯ�ϰ� �Լ��� �����Ѵ�.
		if (instart == inend) return node;
		else {
			// inorder���� node->item�� ã��, �� �ε����� �������� �¿�� Ʈ���� �����Ѵ�.
			int inindex = Search(inorder, node->item, instart, inend);
			if (inindex != -1) {
				node->left_child = MakeTree(preorder, inorder, instart, inindex - 1);
				node->right_child = MakeTree(preorder, inorder, inindex + 1, inend);
			}
			return node;
		}
	}
}

// �� ���� ������ ���, �� �� �������� �ε����� �־��ش�. 
int main() {
	// ����� ������ �Է¹޴´�.
	int N;
	scanf("%d", &N);
	rewind(stdin);

	// preorder, inorder ����� ������ ������ �Ҵ��ϰ� �Է��� �޴´�.
	char* prestr = (char*)malloc(sizeof(char) * 4 * N);
	char* instr = (char*)malloc(sizeof(char) * 4 * N);

	scanf("%[^\n]s", prestr);
	rewind(stdin);
	scanf("%[^\n]s", instr);
	rewind(stdin);


	// ������ �Է¹��� ���� ����� ������ �ٲ㼭 �����Ѵ�.
	int* preorder = StrToNum(prestr, N);
	int* inorder = StrToNum(instr, N);

	BTreeNode* node = MakeTree(preorder, inorder, 0, N - 1);
	Postorder(node);

	return 0;
}