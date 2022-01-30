/*
��Ŀ��
����һ��n �� m�ľ�����������ÿ����λ����������𻵡�Ҫ���ҵ����������в�����������������εĸ�����

���룺��һ����������n,m��ʾ��������Ĵ�С��
����������n���������ݣ�ÿ�а���m��0��1������������0��ʾ�õ�����ã�1��ʾ�õ������𻵡�

��������һ��������ʾ�����ڵ������θ�����
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

struct Rectangle {
    int number;    // �Ե�(i,j)Ϊ���½ǣ��ɹ��ɵ������θ���
    int col;    // ��(i,j)����������0�ĸ���
    int row;    // ��(i,j)����������0�ĸ���
    int total;  // (0,0)->(i,j) ��Χ�������θ���
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

    for (int j = 1; j <= m; j++){//��һ��
        dp[1][j].total = dp[1][j - 1].total + (1 - A[1][j]);
        dp[1][j].number = 1 - A[1][j];
        dp[1][j].col = 1 - A[1][j];
        dp[1][j].row = (A[1][j] == 1) ? 0 : dp[1][j - 1].row + 1;
    }

    for (int i = 2; i <= n; i++){//��A[2][1]��ʼ
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
                dp[i][j].total = dp[i - 1][j].total + dp[i][j - 1].total - dp[i - 1][j - 1].total;//��ȥ�ظ���������
            }
        }
    }
    printf("%d",dp[n][m].total);
    return 0;
}