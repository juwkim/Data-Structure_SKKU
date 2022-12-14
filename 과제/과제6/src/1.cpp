# include <stdio.h>
# include <string.h>
# include <malloc.h>

typedef struct {
	int pos;
	int brightNess;
	int order;
} Node;

void SWAP(Node* a, Node* b) {
	Node temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(Node* Road, int left, int right, int pb) {
	// pos 정렬이면 pb 1, brightNess 정렬이면 pos 0;
	// 내림차순 정렬;
	int low = left + 1, high = right;
	if (pb) {
		int pivot = (Road + left)->pos;
		while (1) {
			while (low < right && (Road + low)->pos < pivot)
				low++; // Move low until pivot <= (Road + low)->pos
			while (high > left && (Road + high)->pos >= pivot)
				high--; // Move high until pivot > (Road + high)->pos
			if (low < high)
				// Swap Road[low] and Road[high].
				SWAP(Road + low, Road + high);
			else break;
		}
	}
	// 오름차순 정렬
	else {
		int pivot = (Road + left)->brightNess;
		while (1) {
			while (low < right && (Road + low)->brightNess > pivot)
				low++; // Move low until pivot <= (Road + low)->brightNess
			while (high > left && (Road + high)->brightNess <= pivot)
				high--; // Move high until pivot > (Road + high)->brightNess

			if (low < high)
				// Swap Road[low] and Road[high].
				SWAP(Road + low, Road + high);
			else break;
		}
	}
	SWAP(Road + left, Road + high);
	return high; //return the pivot position.
}
void QuickSort(Node* Road, int left, int right, int pb) {
	if (left < right) {
		// The mid refers to the pivot position.
		int mid = Partition(Road, left, right, pb);
		// All elements are less than the pivot.
		QuickSort(Road, left, mid - 1, pb);
		// All elements are greater than the pivot.
		QuickSort(Road, mid + 1, right, pb);
	}
}

int search_p(Node* Road, int start, int end, int target, int c) {
	// min 값을 찾는 거면 c = 0; max값을 찾는 거면 c = 1;
	if (end > start) {
		int mid = (start + end) / 2;
		if ((Road + mid)->pos == target) return mid;
		else if (((Road + mid)->pos > target)) return search_p(Road, start, mid - 1, target, c);
		else return search_p(Road, mid + 1, end, target, c);
	}
	// 찾는 값이 없다. 그러므로 찾는 값에 가장 가까운 인덱스를 return 한다.
	else if (c) return start; // end <= start 일때, 더 큰 start를 return 한다.
	else return end;// end <= start 일때, 더 작은 end를 return 한다.
}
int search_b(Node* Road, int start, int end, int target, int pos_check) {
	if (end > start) {
		int mid = (start + end) / 2;
		//printf("mid: %d\n", mid);
		if ((Road + mid)->brightNess == target) {
			if ((Road + mid)->pos == pos_check) {
				//printf("(Road + mid)->brightNess == target %d\n", (Road + mid)->brightNess);
				return mid;
			}
			int z = 1;
			while (1) {
				if ((Road + mid + z)->pos == pos_check) return mid + z;
				if ((Road + mid - z)->pos == pos_check) return mid - z;
				z++;
			}
		}
		else if (((Road + mid)->brightNess < target)) {
			//printf("(Road + mid)->brightNess < target %d\n", (Road + mid)->brightNess);
			return search_b(Road, start, mid - 1, target, pos_check);
		}
		else {
			//printf("(Road + mid)->brightNess > target %d\n", (Road + mid)->brightNess);
			return search_b(Road, mid + 1, end, target, pos_check);
		}
	}
}
void Remove(Node* Road_p, Node* Road_b, int N, int* count, int* total_cal) {
	int Bpos, Bbright;
	int Ppos, Pbright;
	int index_min, index_max, index_b;
	int small, big, min, max;
	int i, j;

	for (i = 0; i < N - 1; i++) {
		// 다른 램프의 범위 안에 들어가는 램프의 pos을 0으로 만든다.
		// 이러한 램프는 고려하지 않는다.
		Bpos = (Road_b + i)->pos;
		Bbright = (Road_b + i)->brightNess;
		if (Bpos) {
			min = Bpos - Bbright;
			max = Bpos + Bbright;
			index_min = search_p(Road_p, 0, N - 1, min, 0);
			index_max = search_p(Road_p, 0, N - 1, max, 1);

			*total_cal += 4;
			for (j = index_min; j <= index_max; j++) {
				Ppos = (Road_p + j)->pos;
				Pbright = (Road_p + j)->brightNess;
				if (Ppos) {
					small = Ppos - Pbright;
					big = Ppos + Pbright;
					if (((min <= small) && (big < max)) || ((min < small) && (big <= max))) {
						(*count)--;

						if (Pbright < Bbright) {
							index_b = search_b(Road_b, 0, N - 1, (Road_p + j)->brightNess, (Road_p + j)->pos);
							//printf("포지션 %d 밝기 %d가 포지션 %d 밝기 %d에 의해 제거되었습니다.\n", (Road_p + j)->pos, (Road_p + j)->brightNess, (Road_b + i)->pos, (Road_b + i)->brightNess);
							*total_cal += 1;
							(Road_b + index_b)->pos = 0;
							//printf("index_b %d\n", index_b);
						}
						(Road_p + j)->pos = 0;
					}
				}
			}
		}
	}
}
void printTest(Node* Road_p, int N) {
	for (int i = 0; i < N; i++) {
		if ((Road_p + i)->pos) printf("%d %d\n", (Road_p + i)->order, (Road_p + i)->pos);
		else printf("%d %d\n", 0, (Road_p + i)->pos);
	}
}

void print(Node* Road_p, int N) {
	for (int i = 0; i < N; i++) {
		if ((Road_p + i)->pos) printf("%d ", (Road_p + i)->order);
	}
}

int main() {
	int N, pos, brightNess;
	scanf("%d", &N);

	Node* Road_p = (Node*)malloc(sizeof(Node) * N);
	Node* Road_b = (Node*)malloc(sizeof(Node) * N);

	for (int num = 0; num < N; num++) {
		scanf("%d %d", &pos, &brightNess);
		Node Lamp;
		Lamp.pos = pos;
		Lamp.brightNess = brightNess;
		Lamp.order = num + 1;
		*(Road_p + num) = Lamp;
		*(Road_b + num) = Lamp;
	}
	//memcpy(Road_b, Road_p, sizeof(Node) * N);B
	/*
	printf("Before Road_p\n");
	for (int num = 0; num < N; num++) {
		printf("pos brightNess order\n");
		printf("%d %d %d\n", (Road_p + num)->pos, (Road_p + num)->brightNess, (Road_p + num)->order);
	}

	printf("Before Road_b\n");
	for (int num = 0; num < N; num++) {
		printf("pos brightNess order\n");
		printf("%d %d %d\n", (Road_b + num)->pos, (Road_b + num)->brightNess, (Road_b + num)->order);
	}
	*/
	QuickSort(Road_p, 0, N - 1, 1);
	QuickSort(Road_b, 0, N - 1, 0);
	/*
	printf("After Road_p\n");
	printf("pos brightNess order\n");
	for (int num = 0; num < N; num++) {
		printf("%d %d %d\n", (Road_p + num)->pos, (Road_p + num)->brightNess, (Road_p + num)->order);
	}

	printf("After Road_b\n");
	printf("pos brightNess order\n");
	for (int num = 0; num < N; num++) {
		printf("%d %d %d\n", (Road_b + num)->pos, (Road_b + num)->brightNess, (Road_b + num)->order);
	}
	*/

	int count = N;
	int total_cal = 0;
	Remove(Road_p, Road_b, N, &count, &total_cal);

	printf("%d\n", count);
	print(Road_p, N);
	//printf("\n총 계산은 %d회 입니다.", total_cal);
	//printTest(Road_p, N);
	/*
	printf("start print\n");
	for (int num = 0; num < N; num++) {
		printf("*(Road + num): %d %d\n", (*(Road_p + num)).pos, (*(Road_p + num)).brightNess);
	}
	*/
	return 0;
}