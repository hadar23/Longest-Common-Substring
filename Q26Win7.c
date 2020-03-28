#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int m, n, **c;
char *x, *y, **b;

// print the longest substring
void printAnswer(int i, int j) {
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 'c') {
		printAnswer(i - 1, j - 1);
		printf("%c", x[i - 1]);
	} else if (b[i][j] == 'u')
		printAnswer(i - 1, j);
	else
		printAnswer(i, j - 1);
}

// do the calculations
void lcs() {
	int i, j;
	for (i = 0; i <= m; i++)
		c[i][0] = 0;
	for (i = 0; i <= n; i++)
		c[0][i] = 0;

	// c = ↖ or \
	// u = ↑
	// l = ←
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'c';
			} else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 'u';
			} else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 'l';
			}
		}
}

// print B matrix and free it
void printAndFreeB() {
	int i, j;
	int first = 0;
	printf("\n\nB:\n");
	/* see all the signs that the OS can write in cmd
	for(i = 0;i < 1000; i++){
		printf(" %d %c ", i, i);
	}*/

	printf("    ");
	for (i = 0; i < n + 1; i++) {
		printf("%d ", i);
	}
	printf("\n");
	printf("    Y ");
	for (i = 0; i < n + 1; i++) {
		printf("%c ", y[i]);
	}
	printf("\n");
	printf("0 X ");

	for (i = 0; i < m + 1; i++) {
		if (first != 0)
			printf("%d %c ", i, x[i - 1]);
		first++;
		for (j = 0; j < n + 1; j++) {
			if (i == 0 || j == 0) {
				printf("0 ");
				continue;
			}
			if (b[i][j] == 'c') {
				printf("\\ ");
			} else if (b[i][j] == 'u') {
				printf("%c ", 24);
			} else {
				printf("%c ", 27);
			}
		}
		free(b[i]);
		printf("\n");
	}
	free(b);
}

// print C matrix and free it
void printAndFreeC() {
	int i, j;
	int first = 0;
	printf("\n\nC:\n");

	printf("    ");
	for (i = 0; i < n + 1; i++) {
		printf("%d ", i);
	}
	printf("\n");
	printf("    Y ");
	for (i = 0; i < n + 1; i++) {
		printf("%c ", y[i]);
	}
	printf("\n");
	printf("0 X ");

	for (i = 0; i < m + 1; i++) {
		if (first != 0)
			printf("%d %c ", i, x[i - 1]);
		first++;
		for (j = 0; j < n + 1; j++) {
			printf("%d ", c[i][j]);
		}
		free(c[i]);
		printf("\n");
	}
	free(c);
}

// set C and B matrices at start
void setCAndB() {
	int i;
	c = (int**) calloc(m + 1, sizeof(int*));
	b = (char**) calloc(m + 1, sizeof(char*));
	for (i = 0; i < m + 1; i++) {
		c[i] = (int*) calloc(n + 1, sizeof(int));
		b[i] = (char*) calloc(n + 1, sizeof(char));
	}
}

// get M (size of X) and N (size of Y) and X (string) and Y (string) from user
void getMNXY() {
	printf("Enter 1st sequence length:");
	scanf("%d", &m);
	x = (char*) calloc(m + 1, sizeof(char));
	printf("Enter 1st sequence:");
	scanf("%s", x);

	printf("Enter 2nd sequence length:");
	scanf("%d", &n);
	y = (char*) calloc(n + 1, sizeof(char));
	printf("Enter 2nd sequence:");
	scanf("%s", y);
}

// wait for an answer from the user (play again or exit)
int waitForACharToEnd(){
	int c = 0;
	printf("\nPress 1 to play again\nPress 0 to exit\n");
	scanf("%d", &c);
	return c;
}

// main function
int main() {
	int again = 1;
	while (again == 1) {
		again = 0;
		getMNXY();
		setCAndB();
		lcs();
		printf("\nThe Longest Common Subsequence is: ");
		printAnswer(m, n);
		printAndFreeC();
		printAndFreeB();
		again = waitForACharToEnd();
	}
	return 1;
}
