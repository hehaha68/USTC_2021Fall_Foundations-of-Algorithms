/*
题目：输入一个长度为N的数组，你需要求出数组中逆序对的数量，
答案对10,000,007取模。逆序对即对于数组A，满足i<j，Ai>Aj的(i,j)对。

输入：输入一共两行，第一行为一个数字N，第二行一共有N个数字。
0<N≤1,000,000，0≤Ai​≤1e8。

输出：输出共一个整数。
因为输出值可能非常大，请将输出的答案模10,000,007。

例子：
Input：
6
6 1 6 4 1 9
Output：
6
*/

#include<stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000000000

int merge(int A[], int p, int q, int r) {
    int i, j, k, num = 0, FLAG;
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L,*R;

    L = (int*)malloc((n1+2) * sizeof(int));
    R = (int*)malloc((n2+2) * sizeof(int));

    for (i = 1; i <= n1; i++) 
        L[i] = A[p + i - 1];
    for (j = 1; j <= n2; j++) 
        R[j] = A[q + j];

    L[n1+1] = MAX;
    R[n2+1] = MAX;
    FLAG = 0;

    for (i = 1, j = 1, k = p; k <= r; k++) {
        if (FLAG == 0 && R[j] < L[i]) {
            num = (num + n1-i+1) % 10000007;
            FLAG = 1;
        }

        if (L[i] <= R[j])
            A[k] = L[i++];
        else {
            A[k] = R[j++];
            FLAG = 0;
        }
    }
    free(L);
    free(R);

    return num % 10000007;;
}

int merge_sort(int A[], int p, int r) {
    if (p < r) {
        int q,num = 0;
        q = floor((p + r) / 2);
        num = (num + merge_sort(A, p, q)) % 10000007;
        num = (num + merge_sort(A, q + 1, r)) % 10000007;
        num = (num + merge(A, p, q, r)) % 10000007;
        return num % 10000007;;
    }
    else {
        return 0;
    }
}

int main() {
    int i,N,num;
    int* A;

    scanf("%d", &N);
    A = (int*)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
        scanf("%d", &A[i]);
    num = merge_sort(A, 0, N-1);
    printf("%d", num % 10000007);
    free(A);

    return 0;
}