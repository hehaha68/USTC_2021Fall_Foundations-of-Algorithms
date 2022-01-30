/*
题目：
现有一个n × m的矩形区域，其中每个单位区域可能有损坏。要求找到地面上所有不包含损坏区域的正方形的个数。

输入：第一行两个整数n,m表示矩形区域的大小。
接下来共有n行输入数据，每行包含m个0或1的整数，其中0表示该地面完好，1表示该地面已损坏。

输出：输出一个整数表示区域内的正方形个数。
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

struct Rectangle {
    int number;    // 以点(i,j)为右下角，可构成的正方形个数
    int col;    // 从(i,j)向上连续的0的个数
    int row;    // 从(i,j)向左连续的0的个数
    int total;  // (0,0)->(i,j) 范围内正方形个数
} dp[2001][2001];

int A[2001][2001];

int Min(const int& x, const int& y, const int& z){
    if (y < z)
        return (x < y) ? x : y;
    else
        return (x < z) ? x : z;
}

int main(){
    int n, m;
    scanf("%d %d", &n,&m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &A[i][j]);

    for (int j = 1; j <= m; j++){//第一行
        dp[1][j].total = dp[1][j - 1].total + (1 - A[1][j]);
        dp[1][j].number = 1 - A[1][j];
        dp[1][j].col = 1 - A[1][j];
        dp[1][j].row = (A[1][j] == 1) ? 0 : dp[1][j - 1].row + 1;
    }

    for (int i = 2; i <= n; i++){//从A[2][1]开始
        dp[i][1].total = dp[i - 1][1].total + (1 - A[i][1]);
        dp[i][1].number = 1 - A[i][1];
        dp[i][1].col = (A[i][1] == 1) ? 0 : dp[i - 1][1].col + 1;
        dp[i][1].row = 1 - A[i][1];

        for (int j = 2; j <= m; j++){
            if (A[i][j] == 0) {
                dp[i][j].number = Min(dp[i - 1][j - 1].number, dp[i - 1][j].col, dp[i][j - 1].row) + 1;
                dp[i][j].col = dp[i - 1][j].col + 1;
                dp[i][j].row = dp[i][j - 1].row + 1;
                dp[i][j].total = dp[i - 1][j].total + dp[i][j - 1].total - dp[i - 1][j - 1].total + dp[i][j].number;
            }
            else{
                dp[i][j].number = 0;
                dp[i][j].col = 0;
                dp[i][j].row = 0;
                dp[i][j].total = dp[i - 1][j].total + dp[i][j - 1].total - dp[i - 1][j - 1].total;//减去重复的正方形
            }
        }
    }
    printf("%d",dp[n][m].total);
    return 0;
}