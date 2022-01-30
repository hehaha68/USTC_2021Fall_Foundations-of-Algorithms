#include<stdio.h>
#include<stdlib.h>

int partition(int* A, int left, int right) {
	int p = A[right];
	int i = left - 1;
	int j;
	for (j = left; j < right; j++) {
		if (A[j] <= p) {
			i = i + 1;
			int t = A[i];
			A[i] = A[j];
			A[j] = t;
		}
	}
	A[right] = A[i + 1];
	A[i + 1] = p;
	return i + 1;
}
int random_select(int* A, int left, int right, int k) {
	if (left == right)
		return A[left];

	int rp = rand() % (right - left + 1) + left;
	int t = A[rp];
	A[rp] = A[right];
	A[right] = t;

	int pivot = partition(A, left, right);
	int position = pivot - left + 1;
	if (position == k)
		return A[pivot];
	if (position < k) {
		return random_select(A, pivot + 1, right, k - position);
	}
	else {
		return random_select(A, left, pivot - 1, k);
	}
}

int main() {
	int num;
	int i;
	int k;
	int T;
	int p;
	scanf("%d", &T);
	for (p = 0; p < T; p++) {

		scanf("%d", &num);
		scanf("%d", &k);

		int* A = (int*)malloc(num * sizeof(int));
		int t;

		for (i = 0; i < num; i++) {
			scanf("%d", &t);
			A[i] = t;
		}

		int target = random_select(A, 0, num - 1, k);
		printf("%d\n", target);
	}
	return 0;
}
