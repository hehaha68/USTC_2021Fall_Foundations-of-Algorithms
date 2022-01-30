/*
题目：在T组数组中，对于每个数组，仅求对该数组从小到大排序后index为K−1的数
（index从0开始）如K=3对数组3 1 5 9，即求1 3 5 9中index为2的数，为5。

输入：首先输入一个正整数T，5≤T≤100，接下来T组输入。在每组输入中，首先输入N K，
N代表数组大小，1≤K≤N≤10^5。接下来一行为N个数字A_i​，表示该数组，0≤A_i​≤10^8。

输出：共输出T行。每一行代表所求的，对数组从小到大排序后index为k-1的数。

例子：
Input：
2
5 3
9 3 5 1 10
4 2
1 2 2 3
Output：
5
2
*/

#include<stdio.h>
#include <stdlib.h>

int PARTITION(int A[], int p, int r) {
	int x, i, j;
	int temp;
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
	int i;
	int temp;
	i = rand() % (r - p + 1) + p;
	temp = A[i];
	A[i] = A[r];
	A[r] = temp;
	return PARTITION(A, p, r);
}

int RANDOMIZED_SELECT( int A[], int p, int r, int i) {
	int q, k;
	if (p == r)
		return A[p];
	q = RANDOMIZED_PARTITION(A, p, r);
	k = q - p + 1;
	if (i == k)
		return A[q];
	else if (i < k)
		return RANDOMIZED_SELECT(A, p, q - 1, i);
	else return RANDOMIZED_SELECT(A, q + 1, r, i - k);
}

int main(){
	int i,j, T, n,k;
	int key[100];
	int* p;
	scanf("%d", &T);
	for (j = 0; j < T; j++) {
		scanf("%d %d", &n,&k);
		p = (int*)malloc((n) * sizeof(int));
		for (i = 0; i < n; i++)
			scanf("%d", &p[i]);
		key[j] = RANDOMIZED_SELECT(p, 0, n-1 , k);
		free(p);
	}
	for (i = 0; i < T; i++)
		printf("%d\n", key[i]);
	return 0;
}