#include <stdio.h>

#define MAX_SIZE 100

typedef int Data;

void SWAP(Data* a, Data* b) {
	Data temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void SelectionSort(Data* list, int n) {
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			// Find an index with the minimum element.
			if (list[j] < list[min]) min = j;
		}
		// Exchange the minimum element and the i-th element.
		SWAP(list + i, list + min);
	}
}

void BubbleSort(Data* list, int n) {
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			// Compare each pair of adjacent items.
			if (list[j] > list[j + 1]) {
				// Swap if they are in the wrong order.
				SWAP(list + j, list + j + 1);
			}
		}
	}
}

void InsertionSort(Data* list, int n) {
	int j, key;
	for (int i = 1; i < n; i++) {
		// Choose the i-th element.
		key = list[i];
		for (j = i - 1; j >= 0; j--) {
			// If the j-th element is greater than key,
			// move to the next position.
			if (key < list[j]) list[j + 1] = list[j];
			else break;
		}
		// list[j] <= key and list[j+1] is empty
		// move the key to the (j+1)-th element.
		list[j + 1] = key;
	}
}

int Partition(Data* list, int left, int right) {
	int pivot = list[left];
	int low = left + 1, high = right;
	while (1) {
		while (low < right && list[low] < pivot)
			low++; // Move low until pivot < L[low]
		while (high > left && list[high] >= pivot)
			high--; // Move high until pivot >= L[low]

		if (low < high)
			// Swap list[low] and list[high].
			SWAP(list + low, list + high);
		else break;
	}
	SWAP(list + left, list + high);
	return high; //return the pivot position.
}

void QuickSort(Data * list, int left, int right) {
	if (left < right) {
		// The mid refers to the pivot position.
		int mid = Partition(list, left, right);
		// All elements are less than the pivot.
		QuickSort(list, left, mid - 1);
		// All elements are greater than the pivot.
		QuickSort(list, mid + 1, right);
	}
}

void Merge(Data* list, int left, int mid, int right) {
	int sorted[MAX_SIZE] = { 0, };
	int first = left, second = mid + 1, i = left;

	// Merge two lists by comparing elements in sequence.
	while (first <= mid && second <= right) {
		if (list[first] <= list[second])
			sorted[i++] = list[first++];
		else sorted[i++] = list[second++];
	}

	// For remaining items, add them in sequence.
	if (first > mid)
		for (int j = second; j <= right; j++)
			sorted[i++] = list[j];
	else
		for (int j = first; j <= mid; j++)
			sorted[i++] = list[j];

	// Copy the sorted list to the list.
	for (int j = left; j <= right; j++)
		list[j] = sorted[j];
}

void MergeSort(Data* list, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;    // Equal partitioning
		MergeSort(list, left, mid);      // Sorting sublists
		MergeSort(list, mid + 1, right); // Sorting sublists
		Merge(list, left, mid, right);   // Merging two sublists
	}
}

int MIN(int a, int b) {
	if (a > b) return a;
	else return b;
}

void IterMergeSort(Data* list, int n) {
	// Merge subarrays in bottom up manner. First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (int size = 1; size <= n - 1; size = 2 * size) {
		// Pick starting point of different subarrays of current size
		for (int left_start = 0; left_start < n - 1; left_start += 2 * size) {
			// Find ending point of left subarray.
			// mid+1 is starting point of right
			int mid = left_start + size - 1;
			int right_end = MIN(left_start + 2 * size - 1, n - 1);

			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			Merge(list, left_start, mid, right_end);
		}
	}
}

void CountingSort(Data* list, int n) {
	Data count[MAX_SIZE] = { 0 };
	Data output[MAX_SIZE];
	// Counting the redundant elemnts
	for (int i = 0; i < n; i++)
		count[list[i]]++;

	// Cumulate the number of elements.
	for (int i = 1; i < MAX_SIZE; i++)
		count[i] += count[i - 1];

	// Read the elements in the list and copy them to the output list.
	// this is unstable
	for (int i = 0; i < n; i++) {
		output[count[list[i]]-- - 1] = list[i];
		//count[list[i]]--;
	}

	// Copy the output list to the original list.
	for (int i = 0; i < n; i++)
		list[i] = output[i];
}

void Counting(Data* list, int n, int exp) {
	int count[10] = { 0 };
	int output[MAX_SIZE];

	// Store count of occurrences in count list.
	for (int i = 0; i < n; i++)
		count[(list[i] / exp) % 10]++;

	// Change count[i] so that count[i] contains
	// actual position of this digit in output list.
	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output list.
	// this is stable
	for (int i = n - 1; i >= 0; i--) {
		output[count[(list[i] / exp) % 10] - 1] = list[i];
		count[(list[i] / exp) % 10]--;
	}

	// Copy the output list to list[], so that list[] now
	// contains sorted numbers according to current digit
	for (int i = 0; i < n; i++)
		list[i] = output[i];
}

void RadixSort(Data* list, int n) {
	// Find the maximum number to know the number of digits.
	int max = list[0];
	for (int i = 1; i < n; i++) {
		if (list[i] > max) max = list[i];
	}

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; max / exp > 0; exp *= 10)
		Counting(list, n, exp);
}

int main() {
	Data a = 3, b = 5;
	SWAP(&a, &b);
	printf("a and b: %d %d\n", a, b);
	return 0;
}
