#include<stdio.h>
#include <stdlib.h>
#define MAX 10000000

int PARTITION(int A[], int p, int r){
	int x, i, j, temp;
	x = A[r];
	i = p - 1;
	for (j = p; j <= r-1; j++) {
		if (A[j] <= x){
			i = i + 1;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	temp = A[i+1];
	A[i+1] = A[r];
	A[r] = temp;
	return i + 1;
}

int RANDOMIZED_PARTITION(int A[], int p, int r) {
	int i,temp;
	i = rand() % (r-p+1)+p;
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


int main() 
{
	int i,n,k,A[MAX];
	scanf_s("%d %d", &n,&k);
	for (i = 0; i < n; i++)
		scanf_s("%d", &A[i]);
	RANDOMIZED_QUICKSORT(A, 0, n-1);
	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("%d ", A[k-1]);
	return 0;
 }