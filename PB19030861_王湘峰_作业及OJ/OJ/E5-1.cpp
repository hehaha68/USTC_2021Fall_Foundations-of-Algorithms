#include<iostream>
#include<algorithm>
using namespace std;

typedef struct edge {
	int u;
	int v;
	int w;
	bool operator<(const edge a)const {
		return this->w < a.w;
	}
}edge;

int findset(int* P, int x) {
	if (x != P[x]) {
		P[x] = findset(P, P[x]);
	}
	return P[x];
}

int main() {
	int n, m;
	cin >> n >> m;
	edge* E = new edge[m];
	int* parent = new int[n + 1];

	for (int i = 0; i < m; i++) {
		cin >> E[i].u >> E[i].v >> E[i].w;
	}
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
	sort(E, E + m);

	int EDGE = 0;
	int i = 0;
	int result = 0;
	while (i < m) {
		int left = findset(parent, E[i].u);
		int right = findset(parent, E[i].v);
		if (left == right) {
			i++;
			continue;
		}
		else {
			EDGE++;
			result += E[i].w;
			parent[right] = left;
		}
		if (EDGE == n - 1) {
			break;
		}
		i++;
	}
	cout << result;
	return 0;
}
