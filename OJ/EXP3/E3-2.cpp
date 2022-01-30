/*
��Ŀ��
����ԱС����Ҫ��n����������ϲ���һ������ĳ�ֹ����ϵ�ԭ��С��ֻ��ʹ��һ��ϵͳ����Merge
���������ڵ�����ϲ�Ϊһ�����顣Merge�����ϲ��������ȷֱ�Ϊn_1, n_2�������ʱ��Ϊn_1+n_2��
�ָ���n������ĳ��ȣ�С����Ҫ�����С��Ҫ�ĺϲ�ʱ�䡣

���룺���빲���С���һ��һ������n��ʾ���鲢�����������
�ڶ���n����������i��������ʾ��i������ĳ��ȡ�

����������һ�����֣���ʾ��С��Ҫ�Ĺ鲢ʱ�䡣
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