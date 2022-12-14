#define MAX_STACK 100
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int Data;
typedef struct {
	Data items[MAX_STACK];
	int top;
} Stack;

// Make stack empty.
void InitStack(Stack* pstack) {
	pstack->top = -1;
}

// Check whether stack is full.
bool IsFull(Stack* pstack) {
	return pstack->top == MAX_STACK - 1;
}

// check whether stack is empty
bool IsEmpty(Stack* pstack) {
	return pstack->top == -1;
}

// Read the item at the top.
Data Peek(Stack* pstack) {
	if (IsEmpty(pstack)) exit(1); //error: empty stack
	return pstack->items[pstack->top];
}

// Insert an item at the top.
void Push(Stack* pstack, Data item) {
	if (IsFull(pstack)) exit(1); //error: stack full
	pstack->items[++(pstack->top)] = item;
}

// Remove the item at the top.
void Pop(Stack* pstack) {
	if (IsEmpty(pstack)) exit(1); //error: empty stack
	--(pstack->top);
}

void ReversePrint(char* s, int len) {
	Stack stack;
	char ch;

	InitStack(&stack);// Make a stack empty.
	// Push characters.
	for (int i = 0; i < len; i++) Push(&stack, s[i]);

	// Pop characters.
	while (!IsEmpty(&stack)) {
		ch = Peek(&stack);
		printf("%c", ch);
		Pop(&stack);
	}
}
