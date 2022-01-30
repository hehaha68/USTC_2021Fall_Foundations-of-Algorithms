#include<stdio.h>
#include <stdlib.h>
#define MAX 10000000

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

int RANDOMIZED_SELECT(int A[], int p, int r,int i) {
	int q,k;
	if (p == r)
		return A[p];
	q = RANDOMIZED_PARTITION(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	else if (i < k)
		return RANDOMIZED_SELECT(A, p, q-1, i);
	else RANDOMIZED_SELECT(A, q+1, r, i-k);
}


int main()
{
	int i, n, k, A[MAX],key;
	scanf_s("%d %d", &n, &k);
	for (i = 0; i < n; i++)
		scanf_s("%d", &A[i]);
	key = RANDOMIZED_SELECT(A, 0, n - 1,k);
	printf("%d ", key);
	return 0;
}