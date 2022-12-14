#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

char* Flip(int itr, char *up, char *down) {
	if (itr == 1) {
		char* fold = (char*)malloc(sizeof(char)+1);
		*fold = *up;
		*(fold + 1) = NULL;

		return fold;
	} else {
		char* fold = (char*)malloc(sizeof(char) * pow(2, itr));
		char* bfold = Flip(itr - 1, up, down);
		int index = 3 * pow(2, itr - 2);

		if (fold) {
			strcpy(fold, bfold);
			strcat(fold, up);
			strcat(fold, bfold);
			free(bfold);
			*(fold + index - 1) = *down;
		}
		return fold;
	}
}

int main() {
	int direction, itr;
	scanf_s("%d %d", &direction, &itr);

	char up[] = "^";
	char down[] = "V";
	char* fold;
	if (direction) fold = Flip(itr, up, down);
	else fold = Flip(itr, down, up);

	printf("%s\n", fold);

	return 0;
}