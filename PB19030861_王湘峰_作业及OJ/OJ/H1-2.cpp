#include<stdio.h>
#include<stdlib.h>

int partition(int* A, int left, int right) {
	int p = A[right];
	int i=left-1;
	int j;
	for (j = left; j < right; j++) {
		if (A[j] <= p) {
			i = i + 1;
			int t = A[i];
			A[i] = A[j];
			A[j] = t;
		}
	}
	A[right] = A[i+1];
	A[i + 1] = p;
	return i + 1;
}
void quicksort(int* A,int left,int right){
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
	int num;
	int i;
	scanf("%d", &num);
	int* A = (int*)malloc(num*sizeof(int));
	int t;
	for(i=0;i<num;i++){
	 scanf("%d",&t);
	 A[i]=t;
	}
	quicksort(A,0,num-1);
  for (i = 0; i < num; i++) {
	  printf("%d ", A[i]);
  }
}
