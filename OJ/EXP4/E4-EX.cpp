/*
��Ŀ��
С����һ���ܳ������¼��Ϲ���N���ȴ������ɵ��·������ڵ������·�֮�������������Ӱ���·�������ʱ�䡣
���磬���ǿ��������������·��ľ������Сֵ������ȫ���·����ɵ��ٶȡ�
����С��ѡ�����е�M���·����ߣ���ʹ��ʣ����·����Ը������ɡ�����N���·������¼��ϵ�λ�ã������
�㷨ʹ�ó���M���·��������·��������Сֵ���

���룺��һ����������N,M��ʾ����N���·������п��Գ���M����
��������N�У�ÿ��һ������$X_i$��ʾ�·������ꡣ

��������һ��������ʾ����M���·������������·��������Сֵ��
*/

#include <algorithm>
#include <iostream>

using namespace std;
int A[200001];

int main(){
    int n, m, min, max, distance, i, num, last;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    sort(A, A + n);
    min = 0;
    max = A[n - 1] - A[0];
    while (min <= max){
        distance = (min + max) / 2;
        num = 1;
        last = A[0];
        for (i = 1; i < n; i++){
            if (A[i] - last >= distance){
                num++;
                last = A[i];
            }
        }
        if (num >= n - m)   min = distance + 1;
        else   max = distance - 1;
    }
    printf("%d",max);
    return 0;
}