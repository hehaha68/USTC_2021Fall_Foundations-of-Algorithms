/*
��Ŀ��
��һ��������������ϵͳ�й���N���ڵ㣬���Ϊ1,2,3,...,N���ڵ�֮���д��ʹ����������ӣ�
ÿ�����ʹ�����ʹ�����������ʹ�������Ϊһ������L����ʾ�ڴ�����L����λ�Ļ���󣬴��ʹ���
�������޷�ʹ�á�������Ҫ�ӽڵ�S��ڵ�T���ͻ�����ڵ�ǰ����ϵͳ�У�������˳�������
�ٵ�λ�Ļ���ӽڵ�S���ڵ�T

���룺��һ��Ϊ4��������N M S T���ֱ����ڵ���������ʹ���Ŀ�������S��Ŀ�����T
������M�У�ÿ�б���һ�����ʹ�����Ϣ������Ϊ$U_i$$V_i$$L_i$����ʽ����ʾһ���ӽڵ�
$U_i$���ڵ�$V_i$������Ϊ$L_i$�Ĵ��ʹ�

��������һ����������ʾ�ڵ�ǰ����ϵͳ�У�������˳��������ٵ�λ�Ļ���ӽڵ�S���ڵ�T
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