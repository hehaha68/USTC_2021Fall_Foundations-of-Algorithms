#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define N 5000
#define M 100000

typedef struct edge
{
    int start;
    int end;
    int nextEdge;
}edge;

edge Edge[M], _Edge[M];
int Edges_from[N], _Edges_from[N];
int Stamp[N];
int Lowest_in[N];
int timeStamp;

int Stack[N];
int top;
bool If_in_Stack[N];

int Component_of[N];
int Size[N];
int InDegree[N];
int Distance[N];
int n, m, _n, _m;

void Tarjan(int u)
{
    timeStamp++;
    Stamp[u] = Lowest_in[u] = timeStamp;
    Stack[++top] = u;
    If_in_Stack[u] = true;
    for (int i = Edges_from[u]; i != 0; i = Edge[i].nextEdge)
    {
        if (Stamp[Edge[i].end] == 0)
        {
            Tarjan(Edge[i].end);
            Lowest_in[u] = min(Lowest_in[u], Lowest_in[Edge[i].end]);
        }
        else
        {
            if (If_in_Stack[Edge[i].end])
                Lowest_in[u] = min(Lowest_in[u], Stamp[Edge[i].end]);

        }
    }
    if (Lowest_in[u] == Stamp[u])
    {
        for (; Stack[top] != 0; top--)
        {
            If_in_Stack[Stack[top]] = false;
            Component_of[Stack[top]] = u;
            Size[u]++;
            if (Stack[top] == u)
                break;
        }
    }
}

void TopoSort()
{
    queue<int> Queue;
    for (int i = 1; i <= n; i++)
    {
        if (Component_of[i] == i && InDegree[i] == 0)
        {
            Queue.push(i);
            Distance[i] = Size[i];
        }
    }
    while (Queue.size() != 0)
    {
        int u = Queue.front();
        Queue.pop();
        for (int i = _Edges_from[u]; i != 0; i = _Edge[i].nextEdge)
        {
            Distance[_Edge[i].end] = max(Distance[_Edge[i].end], Distance[u] + Size[_Edge[i].end]);
            InDegree[_Edge[i].end]--;
            if (InDegree[_Edge[i].end] == 0)
                Queue.push(_Edge[i].end);
        }
    }
}

int main()
{
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        Edge[i].nextEdge = Edges_from[u];
        Edge[i].start = u;
        Edge[i].end = v;
        Edges_from[u] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        if (Stamp[i] == 0)
            Tarjan(i);
    }

    for (int i = 1; i <= m; i++)
    {
        if (Component_of[Edge[i].start] != Component_of[Edge[i].end])
        {
            _m++;
            _Edge[_m].nextEdge = _Edges_from[Component_of[Edge[i].start]];
            _Edge[_m].end = Component_of[Edge[i].end];
            _Edge[_m].start = Component_of[Edge[i].start];
            _Edges_from[Component_of[Edge[i].start]] = _m;
            InDegree[Component_of[Edge[i].end]]++;
        }
    }

    TopoSort();
    int answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (Component_of[i] == i)
            answer = max(answer, Distance[i]);
    }
    cout << answer;
}