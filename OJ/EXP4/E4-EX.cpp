/*
题目：
小明在一个很长的晾衣架上挂了N件等待被晾干的衣服，相邻的两件衣服之间若距离过近会影响衣服的晾干时间。
例如，我们可以用相邻两件衣服的距离的最小值来衡量全部衣服晾干的速度。
现在小明选择将其中的M件衣服撤走，以使得剩余的衣服可以更快晾干。给定N件衣服在晾衣架上的位置，请设计
算法使得撤走M件衣服后相邻衣服距离的最小值最大。

输入：第一行两个整数N,M表示共有N件衣服，其中可以撤走M件。
接下来的N行，每行一个整数$X_i$表示衣服的坐标。

输出：输出一个整数表示撤走M件衣服后最大的相邻衣服距离的最小值。
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