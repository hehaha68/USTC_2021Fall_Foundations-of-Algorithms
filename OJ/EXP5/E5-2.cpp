/*
题目：
小明被困在一个迷宫之中，迷宫中共有N个点，标号分别为1,2,3,...,N，且迷宫只有一个出口。
N个点之间互相有一些道路连通（单向），两个点之间可能有多条道路连通，但是并不存在一条
两端都是同一个点的道路。小明希望知道从当前位置S去往出口T的最短距离是多少。如果不存在
去往出口的道路，输出-1。

输入：第一行为4个整数，N M S T，分别代表节点个数、道路条数、小明当前所处的位置的标号、出口标号
接下来M行，每行表述一条道路，表述为$U_i$$V_i$$W_i$的形式，表示一条从$U_i$到$V_i$，距离为$W_i$的单向边。

输出：如果小明能逃离迷宫，输出从他的位置到出口的最短距离；否则输出$-1$。
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>

#define N 100000
#define M 1000000

using namespace std;

struct edge{
    int v,w,Edge_u_to;
} Edge[M];

int Edge_from[N], Distance[N], Visited[N];

struct V_distance{
    int v,d;
    bool operator<(const V_distance& that) const {
        return this->d > that.d;
    }
};

int main(){
    priority_queue<V_distance> Q;
    int n, m, s, t, u, v, w;
    scanf("%d %d %d %d", &n, &m, &s, &t);

    for (int i = 1; i <= m; i++){
        scanf("%d %d %d", &u, &v, &w);
        Edge[i].w = w;
        Edge[i].v = v;
        Edge[i].Edge_u_to = Edge_from[u];
        Edge_from[u] = i;
    }
    for (int i = 1; i <= n; i++)
        Distance[i] = INT_MAX;

    Distance[s] = 0;
    Q.push({s,0});
    while (!Q.empty()){
        u = Q.top().v;
        Q.pop();
        if (Visited[u])
            continue;
        Visited[u] = 1;
        for (int i = Edge_from[u]; i != 0; i = Edge[i].Edge_u_to){
            v = Edge[i].v;
            if (Distance[v] > Distance[u] + Edge[i].w){
                Distance[v] = Distance[u] + Edge[i].w;
                if (!Visited[v])
                    Q.push({v,Distance[v]});
            }
        }
    }

    if (Distance[t] == INT_MAX)
        printf("-1");
    else
        printf("%d",Distance[t]);
    return 0;
}