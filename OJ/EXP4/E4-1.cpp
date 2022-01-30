/*
题目：
现有N个村庄排成一排，在这些村庄里需要挑选若干村庄搭建基站，其中基站的覆盖半径为R。
假设在村庄i处放置基站，村庄i的坐标为$X_i$，则处在$[X_i - R, X_i + R]$范围内的
村庄都能被该基站所覆盖。
在给出所有村庄坐标的情况下，求使所有村庄都能被基站覆盖所需要的最少的基站个数。

输入：第一行包含两个整数N,R分别表示村庄个数和基站覆盖半径。
接下来的N行每行一个整数$X_i$表示村庄i的坐标。

输出：输出一个整数表示最少需要搭建的基站数目。
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

int A[100001];

int main() {
    int n, r,num=0,i,j;
    scanf("%d %d", &n, &r);

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    sort(A, A + n);
    for (i = 0; i < n; i++) {
        num++;
        for (j = i; j < n && A[j] - A[i] <= r; j++);
        i = j - 1;
        if (i == n - 1) break;
        for (j = i; j < n && A[j] - A[i] <= r; j++);
        i = j - 1;
        if (i == n - 1)  num++;
    }
    printf("%d", num);
	return 0;
}