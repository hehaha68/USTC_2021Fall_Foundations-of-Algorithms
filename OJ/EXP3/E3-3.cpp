/*
��Ŀ��
����һ��������������������ΪW����Ʒ����n����Ʒ���Է��뱳��������ÿ��
��Ʒ��������Ϊw_i����ֵΪv_i����ѡ����Ϊnum_i��
������Է��뱳������Ʒ������ܼ�ֵ��

���룺��һ����������n,W���ֱ��ʾ��Ʒ�����ͱ���������
Ȼ��n����������ÿ����Ʒ����������ֵ�Ϳ�ѡ������

��������һ��������ʾ����װ�뱳��������ֵ��
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

struct Goods {
	int w, v, num;
};
struct Goods G[201];
int dp[201][10001];
bool cmp(struct Goods a, struct Goods b) {
	if (a.v > b.v)
		return true;
	return false;
}

int main() {
	int W, n,i,j,k;
	scanf("%d %d", &n, &W);
	for (i = 0; i < n; i++) 
		scanf("%d %d %d", &G[i].w, &G[i].v, &G[i].num);

	for (i = 0; i < n; i++) {
		for (j = 0; j <= W; j++) {
			for (k = 0; k <= G[i].num && k * G[i].w <= j; k++) {
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - k * G[i].w] + k * G[i].v);
			}
		}
	}
	printf("%d", dp[n][W]);


	return 0;
}