/*
��Ŀ��
���ڶ�άƽ���ϵ���������A(x_1,y_1),,B(x_2,y_2)������ƫ���ϵ<=����ʾx_1<=x_2��y_1<=y_2��
�ָ���ƽ���ϵ����ɵ㣬�����ĵ���Ӽ�Sʹ�ü����е���������֮�������ƫ���ϵ<=������
\forall A,B \in S��A<=B��B<=A������
ֻ��Ҫ����Ӽ�S�Ĵ�С|S|��

���룺��һ��һ������n��ʾ��ĸ�����Ȼ����n�����룬��ʾn��������꣬����ÿ�еĸ�ʽΪ��
x_i y_i����ĺ��������Ϊ���������������ݲ�������ص��ĵ㡣
0<n<=10000, 0<x_i,y_i<=100000��

��������һ��������ʾ�����ܵ��Ӽ�|S|�Ĵ�С��
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

struct Node {
	int x, y;
};
int B[10000],dp[10000];
struct Node A[10000];

bool cmp(struct Node a, struct Node b){
	if (a.x != b.x)
		return (a.x < b.x);
}


int main() {
	int n,result=1;
	scanf("%d", &n);
	for (int i=0; i < n; i++)
		scanf("%d %d", &A[i].x, &A[i].y);

	sort(A, A + n, cmp);

	for (int i = 0; i < n; i++)
		B[i]=A[i].y;

	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (B[i] >= B[j] && (dp[j] + 1 > dp[i])) {
				dp[i] = dp[j] + 1;
			}
		}
		result = max(result, dp[i]);
	}

	printf("%d", result);

	return 0;
}