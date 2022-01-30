/*
题目：
对于二维平面上的任意两点A(x_1,y_1),,B(x_2,y_2)，定义偏序关系<=，表示x_1<=x_2且y_1<=y_2。
现给定平面上的若干点，求最大的点的子集S使得集合中的任意两点之间均满足偏序关系<=，即对
\forall A,B \in S，A<=B或B<=A成立。
只需要输出子集S的大小|S|。

输入：第一行一个整数n表示点的个数。然后是n行输入，表示n个点的坐标，其中每行的格式为：
x_i y_i，点的横纵坐标均为整数，且输入数据不会出现重叠的点。
0<n<=10000, 0<x_i,y_i<=100000。

输出：输出一个整数表示最大可能的子集|S|的大小。
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