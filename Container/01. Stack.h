#pragma once

#define MAX_STACK 100

typedef int Data;
typedef struct {
	Data items[MAX_STACK];
	int top;
} Stack;

// Make stack empty.
void InitStack(Stack* pstack);

// Check whether stack is full.
bool IsFull(Stack* pstack);

// check whether stack is empty
bool IsEmpty(Stack* pstack);

// Read the item at the top.
Data Peek(Stack* pstack);

// Insert an item at the top.
void Push(Stack* pstack, Data item);

// Remove the item at the top.
void Pop(Stack* pstack);

void ReversePrint(char* s, int len);

