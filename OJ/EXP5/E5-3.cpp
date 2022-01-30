/*
题目：
在一个工厂货物运输系统中共有N个节点，编号为1,2,3,...,N，节点之间有传送带（单向）连接，
每个传送带都有使用寿命，传送带的寿命为一个数字L，表示在传送完L个单位的货物后，传送带就
会破损无法使用。现在需要从节点S向节点T传送货物，求在当前传输系统中，最多可以顺利传输多
少单位的货物从节点S到节点T

输入：第一行为4个整数，N M S T，分别代表节点个数、传送带数目、起点标号S、目标点标号T
接下来M行，每行表述一条传送带的信息，表述为$U_i$$V_i$$L_i$的形式，表示一条从节点
$U_i$到节点$V_i$，寿命为$L_i$的传送带

输出：输出一个整数，表示在当前传输系统中，最多可以顺利传输多少单位的货物从节点S到节点T
*/

#include <iostream>
#include <limits.h>
#include<cstring>
#include <queue>
using namespace std;

#define N 501

int rGraph[N][N];
int parent[N];

bool BFS(int s, int t,int n){
    bool visited[N];
    memset(visited, false, sizeof(visited));
    int u,v;
    queue<int> Q;
    Q.push(s);
    visited[s] = true;
    parent[s] = -1;
    parent[0] = -1;

    while (!Q.empty()){
        u = Q.front();
        Q.pop();
        for (v = 1; v <= n; v++){
            if (!visited[v] && rGraph[u][v] > 0){
                Q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int main(){
    int n, m, s, t, u, v, w;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        rGraph[u][v] += w;
    }

    int max_flow = 0;
    while (BFS(s, t, n)){
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]){
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]){
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    printf("%d", max_flow);
    return 0;
}