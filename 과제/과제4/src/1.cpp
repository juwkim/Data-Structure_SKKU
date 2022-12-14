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

// LRC 순서로 Binary Tree를 출력한다.
void Postorder(BTreeNode* root) {
	if (root != NULL) {
		Postorder(root->left_child);
		Postorder(root->right_child);
		printf("%d ", root->item);
	}
}

// 공백으로 구분된 정수 입력을 str로 받아서
// int 형식으로 변환하여 저장한 int*를 반환한다.
int* StrToNum(char* str, int max_count) {
	// 문자열에서 분리한 정수의 개수를 저장할 변수(count)
	// 문자열에서 분리한 정수를 임시로 저장할 변수(num)
	int count = 0, num = 0;
	// 문자열에서 분리한 정수를 저장할 공간을 할당한다.
	int* pnum = (int*)malloc(sizeof(int) * max_count);

	while (count < max_count && *str) {
		if (*str != ' ') {
			// 공백 문자가 아닐 경우, 문자를 숫자로 변경한다.
			num = num * 10 + *str - '0';
		}
		else {
			// 공백 문자라면 num에 숫자 저장이 완료된 것이므로,
			// num을 pnum에 추가한다.
			if (num > 0) {
				*(pnum + count++) = num;
				num = 0;
			}
		}
		str += 1;
	}
	// 마지막 숫자 뒤에는 공백이 없으므로, 마지막 숫자는 위에서 저장이 되지 않는다.
	// 따라서 마지막 숫자도 pnum에 저장한다.
	if (num > 0) *(pnum + count++) = num;

	return pnum;
}

// Pint에서 value를 찾는 함수
int Search(int* Pint, int value, int start, int end) {
	for (int i = start; i <= end; i++)
		if (value == *(Pint + i)) return i;
	return -1;
}

BTreeNode* MakeTree(int* preorder, int* inorder, int instart, int inend) {

	// preindex를 선언한다. 이 때 함수 호출 때마다 0으로 초기화 되지 않게
	// static을 변수 앞에 쓴다.
	static int preindex = 0;

	// inindex가 instart 또는 inend와 같다는 의미이다.
	// 노드가 없다는 의미이므로, NULL을 반환한다.
	if (instart > inend) return NULL;

	else {
		BTreeNode* node = CreateNode(*(preorder + preindex++));

		// 자식 노드가 없다는 의미이므로, node를 반환하고 함수를 종료한다.
		if (instart == inend) return node;
		else {
			// inorder에서 node->item을 찾고, 그 인덱스를 기준으로 좌우로 트리를 분할한다.
			int inindex = Search(inorder, node->item, instart, inend);
			if (inindex != -1) {
				node->left_child = MakeTree(preorder, inorder, instart, inindex - 1);
				node->right_child = MakeTree(preorder, inorder, inindex + 1, inend);
			}
			return node;
		}
	}
}

// 맨 앞의 포인터 들과, 맨 뒤 포인터의 인덱스를 넣어준다. 
int main() {
	// 노드의 갯수를 입력받는다.
	int N;
	scanf("%d", &N);
	rewind(stdin);

	// preorder, inorder 결과를 저장할 공간을 할당하고 입력을 받는다.
	char* prestr = (char*)malloc(sizeof(char) * 4 * N);
	char* instr = (char*)malloc(sizeof(char) * 4 * N);

	scanf("%[^\n]s", prestr);
	rewind(stdin);
	scanf("%[^\n]s", instr);
	rewind(stdin);


	// 위에서 입력받은 정렬 결과를 정수로 바꿔서 저장한다.
	int* preorder = StrToNum(prestr, N);
	int* inorder = StrToNum(instr, N);

	BTreeNode* node = MakeTree(preorder, inorder, 0, N - 1);
	Postorder(node);

	return 0;
}