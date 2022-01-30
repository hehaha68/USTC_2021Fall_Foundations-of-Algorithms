#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
void quicksort(int* A, int left, int right) {
	if (left < right) {
		int rp = rand() % (right - left + 1) + left;
		int t = A[rp];
		A[rp] = A[right];
		A[right] = t;
		int pivot = partition(A, left, right);
		//printf("rp:%d\n", rp);
		quicksort(A, left, pivot - 1);
		quicksort(A, pivot + 1, right);
	}
	return;
}

int main() {
	int i,j,num;
	char *a=(char*)malloc(sizeof(char));
	char* p;
	int len;
	
	j = 0;
	scanf("%d", &num);
	scanf("%s", a);

	char* str = (char*)malloc(num * sizeof(char));
	int* A = (int*)malloc(num * sizeof(int));

	for (i = 0; i < num; i++)
	{
		A[i] = -1;
	}

	scanf("%s",str);

	p = strtok(str, a);
	A[0] = atoi(p);

	while ((p = strtok(NULL, a))) {
		j += 1;
		A[j] = atoi(p);
	}
	len = j + 1;
	quicksort(A, 0, len - 1);

	for (i = 0; i < len; i++) {
		printf("%d ", A[i]);
	}

	return 0;
}
