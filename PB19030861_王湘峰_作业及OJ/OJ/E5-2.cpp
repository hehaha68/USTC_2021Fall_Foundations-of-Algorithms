#include <iostream>
#include <queue>
using namespace std;

typedef struct edge
{
    int end;
    int length;
    int next;
}edge;

typedef struct node
{
    int index;
    int distance;
    bool operator>(const node that) const
    {
        return this->distance > that.distance;
    }
}node;

priority_queue<node, vector<node>, greater<node>> Q;

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    int* Distance = new int[n + 1];
    edge* Edge = new edge[m + 1];
    int* Next_edge = new int[n + 1];
    bool* visited = new bool[n + 1];

    for (int i = 1; i <= n; ++i) {
        Distance[i] = 65535;
        Next_edge[i] = 0;
        visited[i] = false;
    }

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Edge[i].length = w;
        Edge[i].end = v;
        Edge[i].next = Next_edge[u];     // ��һ����uΪ���ı�
        Next_edge[u] = i;                // ������uΪ���ı�
    }

    Distance[s] = 0;
    Q.push(node{ s,0 });
    while (!Q.empty())
    {
        int x = Q.top().index; // ��ͷ���
        Q.pop();
        if (visited[x]) // �ѱ����ʹ�
            continue;
        visited[x] = true;
        for (int i = Next_edge[x]; i != 0; i = Edge[i].next) // ������xΪ���ı�
        {
            int y = Edge[i].end; // �ߵ��յ�
            if (Distance[y] > Distance[x] + Edge[i].length)
            {
                Distance[y] = Distance[x] + Edge[i].length;
                if (!visited[y])
                    Q.push(node{ y, Distance[y] });
            }
        }
    }
    if (Distance[t] == 65535)
        cout << -1;
    else
        cout << Distance[t];
    return 0;
}