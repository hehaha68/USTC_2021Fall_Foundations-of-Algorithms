#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct job {
	int a;
	int p;
	int r;
	bool operator<(const job b) const {
		if (this->r == b.r) {
			return this->a < b.a;
		}
		else {
			return this->r < b.r;
		}
	}
	bool operator>(const job b)const {
		if (this->r == b.r) {
			return this->a > b.a;
		}
		else {
			return this->r > b.r;
		}
	}
}job;

int sort_by_arrival(const job& x, const job& y) {
	if (x.a == y.a) {
		return x.r < y.r;
	}
	else {
		return x.a < y.a;
	}
}

int main() {
	int n;
	cin >> n;
	job* j = new job[n];
	for (int i = 0; i < n; i++) {
		cin >> j[i].a >> j[i].p;
		j[i].r = j[i].p;
	}
	sort(j, j + n, sort_by_arrival);
	priority_queue<job, vector<job>, greater<job>>Q;
	Q.push(j[0]);
	int interval = 0;
	int response = 0;
	for (int i = 1; i < n; i++) {
		interval = j[i].a - j[i - 1].a;
		job t = Q.top();
		Q.pop();
		while (t.r <= interval) {
			response += j[i].a - interval + t.r - t.a;
			interval -= t.r;
			t.r = 0;
			if (Q.empty()) break;
			else {
				t = Q.top();
				Q.pop();
			}
		}
		t.r -= interval;
		if (t.r > 0) { Q.push(t); }
		Q.push(j[i]);
	}
	int start = j[n - 1].a;
	while (!Q.empty()) {
		job t = Q.top();
		Q.pop();
		response += start + t.r - t.a;
		start += t.r;
	}
	cout << response;
}