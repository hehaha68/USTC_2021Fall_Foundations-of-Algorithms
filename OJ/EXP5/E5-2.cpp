/*
��Ŀ��
С��������һ���Թ�֮�У��Թ��й���N���㣬��ŷֱ�Ϊ1,2,3,...,N�����Թ�ֻ��һ�����ڡ�
N����֮�以����һЩ��·��ͨ�����򣩣�������֮������ж�����·��ͨ�����ǲ�������һ��
���˶���ͬһ����ĵ�·��С��ϣ��֪���ӵ�ǰλ��Sȥ������T����̾����Ƕ��١����������
ȥ�����ڵĵ�·�����-1��

���룺��һ��Ϊ4��������N M S T���ֱ����ڵ��������·������С����ǰ������λ�õı�š����ڱ��
������M�У�ÿ�б���һ����·������Ϊ$U_i$$V_i$$W_i$����ʽ����ʾһ����$U_i$��$V_i$������Ϊ$W_i$�ĵ���ߡ�

��������С���������Թ������������λ�õ����ڵ���̾��룻�������$-1$��
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