#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#define N 501
using namespace std;

typedef struct edge
{
    int to;
    int capacity;
    int next;
    edge(int to, int capacity, int nextEdge) : to(to), capacity(capacity), next(nextEdge)
    {
    }
}edge;
vector<edge> Edges_from[N];
vector<int> Nodes_with_Height_of[N];
list<int> Nodes_with_Height[N];
vector<int> Height;
vector<int> Gap;
vector<int> Q;
vector<int> ExcessFlow;
vector<list<int>::iterator> Iterator;

int highest;
int nowHeight;

int n;
int m;
int s;
int t;

void Relabel()
{
    Height.assign(n + 1, n + 1);
    Height[t] = 0;
    Gap.assign(n + 1, 0);
    Q.clear();
    Q.resize(n + 2);
    int rear = 1;
    Q[0] = t;

    for (int head = 0; head < rear; head++)
    {
        int u = Q[head];
        for (vector<edge>::iterator i = Edges_from[u].begin(); i != Edges_from[u].end(); i++)
        {
            if (Height[i->to] == n + 1 && Edges_from[i->to][i->next].capacity > 0)
            {
                Height[i->to] = Height[u] + 1;
                Gap[Height[i->to]]++;
                Q[rear] = i->to;
                rear++;
            }
        }
    }
    for (int i = 0; i <= n + 1; i++)
    {
        Nodes_with_Height_of[i].clear();
        Nodes_with_Height[i].clear();
    }
    for (int u = 0; u <= n; u++)
    {
        if (Height[u] <= n)
        {
            Iterator[u] = Nodes_with_Height[Height[u]].insert(Nodes_with_Height[Height[u]].begin(), u);
            if (ExcessFlow[u] > 0)
                Nodes_with_Height_of[Height[u]].push_back(u);
        }
    }
    highest = nowHeight = Height[Q[rear - 1]];
}

void Push_to_Edge(int u, edge& e)
{
    int flow = min(ExcessFlow[u], e.capacity);
    e.capacity -= flow;
    Edges_from[e.to][e.next].capacity += flow;
    ExcessFlow[u] -= flow;
    ExcessFlow[e.to] += flow;
    if (0 < ExcessFlow[e.to] && ExcessFlow[e.to] <= flow)
        Nodes_with_Height_of[Height[e.to]].push_back(e.to);
}

void Push(int u)
{
    int newHeight = n + 1;
    for (vector<edge>::iterator i = Edges_from[u].begin(); i != Edges_from[u].end(); i++)
    {
        if (i->capacity > 0)
        {
            if (Height[u] == Height[i->to] + 1)
            {
                Push_to_Edge(u, *i);
                if (ExcessFlow[u] == 0)
                    return;
            }
            else
                newHeight = min(newHeight, Height[i->to] + 1);
        }
    }
    if (Gap[Height[u]] == 1)
    {
        for (int i = Height[u]; i <= highest; i++)
        {
            for (list<int>::iterator j = Nodes_with_Height[i].begin(); j != Nodes_with_Height[i].end(); j++)
            {
                Gap[Height[*j]]--;
                Height[*j] = n + 1;
            }
            Nodes_with_Height[i].clear();
        }
        highest = Height[u] - 1;
    }
    else
    {
        Gap[Height[u]]--;
        Iterator[u] = Nodes_with_Height[Height[u]].erase(Iterator[u]);
        Height[u] = newHeight;
        if (newHeight == n + 1)
            return;
        Gap[newHeight]++;
        Iterator[u] = Nodes_with_Height[newHeight].insert(Nodes_with_Height[newHeight].begin(), u);
        nowHeight = newHeight;
        highest = max(highest, nowHeight);
        Nodes_with_Height_of[newHeight].push_back(u);
    }
}

int main()
{
    cin >> n >> m >> s >> t;
    for (int i = m; i > 0; i--)
    {
        int u, v, l;
        cin >> u >> v >> l;
        Edges_from[u].push_back(edge(v, l, Edges_from[v].size()));
        Edges_from[v].push_back(edge(u, 0, Edges_from[u].size() - 1));
    }
    int maxFlow;
    if (s == t)
        maxFlow = 0;
    else
    {
        nowHeight = 0;
        highest = 0;
        Height.assign(n + 1, 0);
        Height[s] = n + 1;
        Iterator.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            if (i != s)
                Iterator[i] = Nodes_with_Height[Height[i]].insert(Nodes_with_Height[Height[i]].begin(), i);
        }
        Gap.assign(n + 1, 0);
        Gap[0] = n;
        ExcessFlow.assign(n + 1, 0);
        ExcessFlow[s] = INT_MAX;
        ExcessFlow[t] = -INT_MAX;
        for (int i = 0; i < (int)Edges_from[s].size(); i++)
            Push_to_Edge(s, Edges_from[s][i]);
        Relabel();
        for (int u; nowHeight >= 0;)
        {
            if (Nodes_with_Height_of[nowHeight].empty())
            {
                nowHeight--;
                continue;
            }
            u = Nodes_with_Height_of[nowHeight].back();
            Nodes_with_Height_of[nowHeight].pop_back();
            Push(u);
        }
        maxFlow = ExcessFlow[t] + INT_MAX;
    }
    cout << maxFlow;
    return 0;
}
