/*
��Ŀ��
����N����ׯ�ų�һ�ţ�����Щ��ׯ����Ҫ��ѡ���ɴ�ׯ���վ�����л�վ�ĸ��ǰ뾶ΪR��
�����ڴ�ׯi�����û�վ����ׯi������Ϊ$X_i$������$[X_i - R, X_i + R]$��Χ�ڵ�
��ׯ���ܱ��û�վ�����ǡ�
�ڸ������д�ׯ���������£���ʹ���д�ׯ���ܱ���վ��������Ҫ�����ٵĻ�վ������

���룺��һ�а�����������N,R�ֱ��ʾ��ׯ�����ͻ�վ���ǰ뾶��
��������N��ÿ��һ������$X_i$��ʾ��ׯi�����ꡣ

��������һ��������ʾ������Ҫ��Ļ�վ��Ŀ��
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