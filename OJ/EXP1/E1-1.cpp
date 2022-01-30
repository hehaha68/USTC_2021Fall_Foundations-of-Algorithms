/*
题目：首先输入一个正整数T，代表存在T组样例。接下来共T组样例，每组样例中首先输入N，
下一行N个正整数。在每组样例中你需要找到是否存在一个“超过一半的数”x（即存在x在这
N个数中出现次数≥(N+1)/2，若存在这样的x请输出x，否则输出-1。

输入：首先输入一个正整数T，1≤T≤20。接下来T组输入，在每组输入中有：1≤N≤10^6，
之后的N个数为正整数且≤10^8

输出：共T组输出，对应每一组的输出。在一组样例中，若存在这样的x请输出x，否则输出-1。

例子：
Input:
1
5
1 3 2 3 3
Output:
3
*/

#include<stdio.h>
#include <stdlib.h>

int FINDX(int *p, int N) {
	int i,max = p[0];
	int* q;
	for (i = 0; i < N; i++)
		if (max < p[i])	
			max = p[i];
	q = (int*)malloc((max+1) * sizeof(int));
	for (i = 0; i <= max; i++)
		q[i]=0;
	for (i = 0; i < N; i++) {
		q[p[i]]++;
		if (q[p[i]] >= (N + 1) / 2) {
			free(q);
			return p[i];
		}
	}
	free(q);
	return -1;
}

int main() {
	int T,N,i,j,result[20];
	int* p;
	scanf("%d", &T);
	for (i = 0; i < T; i++) {
		scanf("%d", &N);
		p = (int*)malloc(N * sizeof(int));
		for (j = 0; j < N; j++)
			scanf("%d", &p[j]);
		result[i] = FINDX(p, N);
		free(p);
	}
	for (i = 0; i < T; i++)
		printf("%d\n", result[i]);
	return 0;
}