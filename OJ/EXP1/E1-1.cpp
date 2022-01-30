/*
��Ŀ����������һ��������T���������T����������������T��������ÿ����������������N��
��һ��N������������ÿ������������Ҫ�ҵ��Ƿ����һ��������һ�������x��������x����
N�����г��ִ�����(N+1)/2��������������x�����x���������-1��

���룺��������һ��������T��1��T��20��������T�����룬��ÿ���������У�1��N��10^6��
֮���N����Ϊ�������ҡ�10^8

�������T���������Ӧÿһ����������һ�������У�������������x�����x���������-1��

���ӣ�
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