/*
题目：
现有一个背包可以容纳总重量为W的物品，有n种物品可以放入背包，其中每种
物品单个重量为w_i，价值为v_i，可选数量为num_i。
输出可以放入背包的物品的最大总价值。

输入：第一行两个整数n,W，分别表示物品件数和背包容量。
然后n行数据描述每种物品的重量、价值和可选数量。

输出：输出一个整数表示可以装入背包的最大价值。
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