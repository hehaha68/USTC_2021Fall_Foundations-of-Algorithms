/*
题目：
现有若干危险品需要放置在A,B两个仓库。当两种特定的危险品放置在相同地点时即可能产生危险。
我们用危险系数\alpha_{i,j}​表示危险品i,j放置在一起的危险程度。一些危险品即使放置在一起
也不会产生任何危险，此时\alpha_{i,j}=0，还有一些危险品即使单独放置也会产生危险，此时
\alpha_{i,i}>0。
定义两个仓库整体的危险系数为\max(\max_{i,j\in A}\alpha_{i,j},\max_{i,j\in B}\alpha_{i,j})​)，
即放置在一起的所有危险品两两组合的危险系数的最大值。现在对于一组给定的危险系数，需要设计
方案使得整体危险系数最小。

输入：输入共m+1行。第一行两个整数n和m表示共有n种危险品，危险品之间的危险组合（危险系数
非零的物品组合）共m种。接下来的m行，每行三个整数i,j,\alpha_{i,j}​，表示(i,j)为危险组合
（i,j可能相等），其危险系数为\alpha_{i,j}>0。0<n≤100,000，0<m≤1,000,000。

输出：去除字符串中T后剩余字符串当作数字从小到大排序后的结果。

例子：
Input:
3 3
1 2 4
2 3 3
1 3 2
Output:
2
*/

#include <stdio.h>
#include <stdlib.h>
#include<algorithm>  
#include <iostream>
using namespace std;

typedef struct Edge_Weight {
    int i, j;
    int w;
}Edge_Weight;

typedef struct Dependency {
    int acc;
    int rej;
}Dependency;

bool cmp(Edge_Weight x, Edge_Weight y) {
    return (x.w > y.w);
}

int CHECK(Dependency A[], int acc) {
    if (A[acc].acc == acc)
        return acc;
    else
        return CHECK(A, A[acc].acc);
}

int main(void) {
    int i, m, n, result = 0;
    int node_i, node_j;
    int node_i_acc, node_j_acc;

    cin >> n >> m;
    Dependency* Dep = (Dependency*)malloc(sizeof(Dependency) * (n + 1));
    Edge_Weight* EW = (Edge_Weight*)malloc(sizeof(Edge_Weight) * (m + 1));

    for (i = 0; i < m; i++)
        cin >> EW[i].i >> EW[i].j >> EW[i].w;

    for (i = 0; i < n + 1; i++) {
        Dep[i].acc = i;
        Dep[i].rej = 0;
    }

    sort(EW, EW + m, cmp);


    for (i = 0; i < m; i++) {

        node_i = EW[i].i;   node_j = EW[i].j;
        node_i_acc = CHECK(Dep, node_i);
        node_j_acc = CHECK(Dep, node_j);

        if (node_i_acc == node_j_acc) {
            result = EW[i].w;
            break;
        }
        if (Dep[node_i].rej > 0 && Dep[node_j].rej > 0) {
            Dep[node_i_acc].acc = CHECK(Dep, Dep[node_j_acc].rej);
            Dep[node_j_acc].acc = CHECK(Dep, Dep[node_i_acc].rej);
        }
        else if (Dep[node_i].rej == 0 && Dep[node_j].rej > 0)
            Dep[node_i_acc].acc = CHECK(Dep, Dep[node_j_acc].rej);

        else if (Dep[node_i].rej > 0 && Dep[node_j].rej == 0)
            Dep[node_j_acc].acc = CHECK(Dep, Dep[node_i_acc].rej);

        Dep[node_i].rej = node_j;
        Dep[node_j].rej = node_i;
    }
    cout << result << endl;
    return 0;
}