#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST 100

typedef int Data;
typedef struct {
	Data items[MAX_LIST];
	int len;
} ArrayList;

// Make a list empty.
void InitList(ArrayList* plist) {
	plist->len = 0;
}

// Check whether the list is empty.
bool IsEmpty(ArrayList* plist) {
	return plist->len == 0;
}

// Check whether the list is full.
bool IsFull(ArrayList* plist) {
	return plist->len == MAX_LIST;
}

// Insert an item at the k-th position.
void InsertMiddle(ArrayList* plist, int pos, Data item) {
	if (IsFull(plist) || pos < 0 || pos > plist->len) exit(1);
	for (int i = plist->len - 1; i >= pos; i--)
		plist->items[i + 1] = plist->items[i];
	plist->items[pos] = item;
	plist->len++;
}

// Remove an item at the k-th position.
void RemoveMiddle(ArrayList* plist, int pos) {
	if (IsEmpty(plist) || pos < 0 || pos >= plist->len) exit(1);
	for (int i = pos; i < plist->len; i++)
		plist->items[i] = plist->items[i + 1];
	plist->len--;
}

// Read an item at the k-th position.
Data ReadItem(ArrayList* plist, int pos) {
	if (IsEmpty(plist) || pos < 0 || pos >= plist->len) exit(1);
	return plist->items[pos];
}

// Print each item in a list in sequence.
void PrintList(ArrayList* plist) {
	for (int i = 0; i < plist->len; i++)
		printf("%d\n", plist->items[i]);
}

int main() {
	return 0;
}
