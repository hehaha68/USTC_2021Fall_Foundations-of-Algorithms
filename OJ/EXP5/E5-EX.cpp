/*
题目：
在一张有向图G中，你需要找出节点数最多的一个节点集合S，使得S中的任意两个节点A B至少满足
“A可达B”或者“B可达A”中的一个。如果A到B有连边，B到C有连边，那么我们认为C对A是可达的，
即A可达C。

输入：第一行为2个整数，N M，分别代表节点个数、边的个数
接下来M行，每行表述一条边的信息，表述为$U_i\ V_i$的形式，表示一条从节点$U_i$到节点$V_i$的边

输出：输出一个数字，表示满足上述条件的最大的集合包含的节点的个数
*/

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define N 5000
#define M 100000

struct edge{
    int u, v, Edge_u_to;
}Edge[M],_Edge[M];

int Edges_u_to[N], _Edges_u_to[N];
int DFN[N], LOW[N];


int DFS_num, In_Stack[N], Set[N], Set_len[N];
int Stack[N], top;
void SCC(int u){
    DFS_num++;
    DFN[u] = LOW[u] = DFS_num;
    Stack[++top] = u;
    In_Stack[u] = 1;
    for (int i = Edges_u_to[u]; i != 0; i = Edge[i].Edge_u_to){
        if (DFN[Edge[i].v] == 0){
            SCC(Edge[i].v);
            LOW[u] = min(LOW[u], LOW[Edge[i].v]);
        }
        else{
            if (In_Stack[Edge[i].v])
                LOW[u] = min(LOW[u], DFN[Edge[i].v]);
        }
    }
    if (LOW[u] == DFN[u]){
        while(Stack[top]){
            In_Stack[Stack[top]] = 0;
            Set[Stack[top]] = u;
            Set_len[u]++;
            if (Stack[top] == u)    break;
            top--;
        }
    }
}

int InDegree[N], Distance[N];
void TopoSort(int n){
    queue<int> Q;
    for (int i = 1; i <= n; i++){
        if (Set[i] == i && InDegree[i] == 0){
            Q.push(i);
            Distance[i] = Set_len[i];
        }
    }
    while (!Q.empty()){
        int u = Q.front();
        Q.pop();
        for (int i = _Edges_u_to[u]; i != 0; i = _Edge[i].Edge_u_to){
            Distance[_Edge[i].v] = max(Distance[_Edge[i].v], Distance[u] + Set_len[_Edge[i].v]);
            InDegree[_Edge[i].v]--;
            if (InDegree[_Edge[i].v] == 0)
                Q.push(_Edge[i].v);
        }
    }
}

int main(){
    int n, m, u, v, w;
    int _n, _m=0;
    int max_set_len = 0;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++){
        scanf("%d %d", &u, &v);
        Edge[i].u = u;
        Edge[i].v = v;
        Edge[i].Edge_u_to = Edges_u_to[u];
        Edges_u_to[u] = i;
    }
    for (int i = 1; i <= n; i++)
        if (DFN[i] == 0)    SCC(i);

    for (int i = 1; i <= m; i++){
        if (Set[Edge[i].u] != Set[Edge[i].v]){
            _m++;
            _Edge[_m].v = Set[Edge[i].v];
            _Edge[_m].u = Set[Edge[i].u];
            _Edge[_m].Edge_u_to = _Edges_u_to[Set[Edge[i].u]];
            _Edges_u_to[Set[Edge[i].u]] = _m;
            InDegree[Set[Edge[i].v]]++;
        }
    }

    TopoSort(n);

    for (int i = 1; i <= n; i++)
        if (Set[i] == i)
            max_set_len = max(max_set_len, Distance[i]);

    printf("%d", max_set_len);
}