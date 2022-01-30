/*
题目：首先输入两个正整数N和T，接下来输入一串只包含数字且长度为N的字符串，
你需要将字符串按T分隔开并删除T，将剩余字符串认为数字，并将数字进行从小到大排序后输出。
在字符串转换为数字的过程中，需要去除前导0。若字符串全为0则视作0。

输入：输入两个正整数N和T，其中5≤N≤10^6,0≤T≤9,接下来一行输入一串只包含数字且长度为N的字符串

输出：去除字符串中T后剩余字符串当作数字从小到大排序后的结果。

例子：
Input:
8 1
01210213
Output:
0 2 2 3
*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int PARTITION(int A[], int p, int r) {
	int x, i, j, temp;
	x = A[r];
	i = p - 1;
	for (j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i = i + 1;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return i + 1;
}

int RANDOMIZED_PARTITION(int A[], int p, int r) {
	int i, temp;
	i = rand() % (r - p + 1) + p;
	temp = A[i];
	A[i] = A[r];
	A[r] = temp;
	return PARTITION(A, p, r);
}

int* RANDOMIZED_QUICKSORT(int A[], int p, int r) {
	int q;
	if (p < r) {
		q = RANDOMIZED_PARTITION(A, p, r);
		RANDOMIZED_QUICKSORT(A, p, q - 1);
		RANDOMIZED_QUICKSORT(A, q + 1, r);
	}
	return A;
}

int main() {
    char s[1000000],T[2]="1";
    char *token;
    int i=0,j,N,A[1000000];

    scanf("%d", &N);
    getchar();
    scanf("%c", &T[0]);
    getchar();
    gets_s(s);

    token = strtok(s, T);
    while (token != NULL) {
        A[i++] = atoi(token);
        token = strtok(NULL, T);
    }

	RANDOMIZED_QUICKSORT(A, 0, i - 1);

    for (j = 0; j < i; j++)
        printf("%d ", A[j]);

    return(0);
}