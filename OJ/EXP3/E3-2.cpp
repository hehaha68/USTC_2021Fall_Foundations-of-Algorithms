/*
题目：
程序员小明需要将n个有序数组合并到一起，由于某种工程上的原因，小明只能使用一个系统函数Merge
将两个相邻的数组合并为一个数组。Merge函数合并两个长度分别为n_1, n_2的数组的时间为n_1+n_2。
现给定n个数组的长度，小明需要求出最小需要的合并时间。

输入：输入共两行。第一行一个整数n表示待归并的数组个数。
第二行n个整数，第i个整数表示第i个数组的长度。

输出：输出共一个数字，表示最小需要的归并时间。
*/
#include <stdio.h>

#define N 201
#define MAX 100000000
#define min(a,b) ((a) <= (b) ? (a) : (b))
int dp[N][N];
int sum[N];

int main(){
    int n,temp,len,i,j,k;
    scanf("%d", &n);
    scanf("%d", &sum[0]);
    for (i = 1; i < n; i++){
        scanf("%d", &temp);
        sum[i] = sum[i - 1] + temp;
    }
    for (len = 2; len <= n; len++){
        for (i = 0; i < n - len + 1; i++){
            j = i + len - 1;
            dp[i][j] = MAX;
            for (k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            dp[i][j] += sum[j] - sum[i - 1];
        }
    }
    printf("%d", dp[0][n - 1]);
    return 0;
}