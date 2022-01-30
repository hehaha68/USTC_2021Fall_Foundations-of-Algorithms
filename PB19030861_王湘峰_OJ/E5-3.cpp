// Highest Label Preflow Push
#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#define N 501

using namespace std;

// ��ʽǰ����
struct edge
{
    int to;       // �յ�
    int capacity; // ����
    int nextEdge; // ��һ����ͬ���ߵ��±�
    edge(int to, int capacity, int nextEdge) : to(to), capacity(capacity), nextEdge(nextEdge)
    {
    }
};
vector<edge> Edges_from[N];           // ��ͬ���ı�
vector<int> Nodes_with_Height_of[N]; // ����ͬһ�߶ȵĽ��
list<int> _Nodes_with_Height_of[N];  // ����ͬһ�߶ȵĽ�㣬���ٲ���ɾ��
vector<int> Height;                  // ���ĸ߶�
vector<int> Gap;                     // ͬһ�߶ȵĽ����
vector<int> Queue;                   // һ���Ը߶�Ϊ��ֵ�����ȶ��У�ÿ�ζ������߶���ߵĽڵ㡣
vector<int> ExcessFlow;              // ������
vector<list<int>::iterator> Iterator;

int highest;   // ��߸߶�
int nowHeight; // ��ǰ�߶�

int n; // ����
int m; // ����
int s; // Դ��
int t; // ���

/*
    ������ǩ������������صĽ��ĸ߶�
    �����ISAP�Ĳ���ƫ�ƣ�һ�ο���̧�߲�ֹһ����λ�߶ȣ���һ��ʹ�����е�����ǡ����������һ�����
    ���ұ�ǩ��������ȫͼ�ģ�������BFS�Ĵ��������Ч�ʣ��Ҳ���Ҫʵ��ʵ�����ȶ���
*/
void Relabel()
{
    Height.assign(n + 1, n + 1);
    Height[t] = 0;
    Gap.assign(n + 1, 0);
    Queue.clear();
    Queue.resize(n + 2);
    int rear = 1;
    Queue[0] = t;
    // ȫ�ֵı�ǩ����
    for (int head = 0; head < rear; head++)
    {
        int u = Queue[head];
        for (vector<edge>::iterator i = Edges_from[u].begin(); i != Edges_from[u].end(); i++)
        {
            if (Height[i->to] == n + 1 && Edges_from[i->to][i->nextEdge].capacity > 0)
            {
                Height[i->to] = Height[u] + 1;
                Gap[Height[i->to]]++;
                Queue[rear] = i->to;
                rear++;
            }
        }
    }
    for (int i = 0; i <= n + 1; i++)
    {
        Nodes_with_Height_of[i].clear();
        _Nodes_with_Height_of[i].clear();
    }
    for (int u = 0; u <= n; u++)
    {
        if (Height[u] <= n)
        {
            Iterator[u] = _Nodes_with_Height_of[Height[u]].insert(_Nodes_with_Height_of[Height[u]].begin(), u);
            if (ExcessFlow[u] > 0)
                Nodes_with_Height_of[Height[u]].push_back(u);
        }
    }
    highest = nowHeight = Height[Queue[rear - 1]]; // ��β��ʱΪ���
}

/*
    �����u�洢�ĳ������������e����
*/
void Push_to_Edge(int u, edge& e)
{
    int flow = min(ExcessFlow[u], e.capacity);
    e.capacity -= flow;
    Edges_from[e.to][e.nextEdge].capacity += flow;
    ExcessFlow[u] -= flow;
    ExcessFlow[e.to] += flow;
    if (0 < ExcessFlow[e.to] && ExcessFlow[e.to] <= flow)
        Nodes_with_Height_of[Height[e.to]].push_back(e.to);
}

/*
    ��һ�����洢�ĳ��������ݸ�����ֱ�����ڵĽ��
    ���������·�����������޸ĵ�ǰ�����������������ճ�����
*/
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
    if (Gap[Height[u]] == 1) // �ϲ�
    {
        for (int i = Height[u]; i <= highest; i++)
        {
            for (list<int>::iterator j = _Nodes_with_Height_of[i].begin(); j != _Nodes_with_Height_of[i].end(); j++)
            {
                Gap[Height[*j]]--;
                Height[*j] = n + 1;
            }
            _Nodes_with_Height_of[i].clear();
        }
        // ɾ����Height[u]һֱ����ǰ����߸߶�highest֮�����еĽ��
        highest = Height[u] - 1; // ������߸߶�
    }
    else
    {
        Gap[Height[u]]--;
        Iterator[u] = _Nodes_with_Height_of[Height[u]].erase(Iterator[u]);
        Height[u] = newHeight;
        if (newHeight == n + 1)
            return;
        Gap[newHeight]++;
        Iterator[u] = _Nodes_with_Height_of[newHeight].insert(_Nodes_with_Height_of[newHeight].begin(), u);
        nowHeight = newHeight;
        highest = max(highest, nowHeight);
        Nodes_with_Height_of[newHeight].push_back(u);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    for (int i = m; i > 0; i--)
    {
        int u, v, l;
        cin >> u >> v >> l;
        Edges_from[u].push_back(edge(v, l, Edges_from[v].size()));     // ��Ӵ�u��v����Ϊl�������
        Edges_from[v].push_back(edge(u, 0, Edges_from[u].size() - 1)); // ��Ӵ�v��u����Ϊ0�ķ����
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
                Iterator[i] = _Nodes_with_Height_of[Height[i]].insert(_Nodes_with_Height_of[Height[i]].begin(), i);
        }
        Gap.assign(n + 1, 0);
        Gap[0] = n;
        ExcessFlow.assign(n + 1, 0);
        ExcessFlow[s] = INT_MAX;
        ExcessFlow[t] = -INT_MAX; // ��ֹ���
        for (int i = 0; i < (int)Edges_from[s].size(); i++)
            Push_to_Edge(s, Edges_from[s][i]);
        Relabel(); // ������ǩ
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
        maxFlow = ExcessFlow[t] + INT_MAX; // �ָ���㳬����
    }
    cout << maxFlow;
    return 0;
}