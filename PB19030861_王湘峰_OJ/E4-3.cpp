#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

typedef struct data {
	int index;
	int next;
	bool operator>(const data t)const {
		return this->next > t.next;
	}
	bool operator<(const data t)const {
		return this->next < t.next;
	}
}Data;

int main() {
	int n, k;
	cin >> n >> k;

	Data* next_arrival = new Data[n];
	for (int i = 0; i < n; i++) {
		cin >> next_arrival[i].index;
	}

	int* Memory = new int[10000];
	//memset(Memory, 10001, sizeof(Memory));
	for (int i = 0; i < 10000; i++) {
		Memory[i] = 10001;
	}

	for (int i = n - 1; i >= 0; i--) {
		next_arrival[i].next = Memory[next_arrival[i].index];
		Memory[next_arrival[i].index] = i;
	}

	priority_queue<Data, vector<Data>>Q;
	bool* cache = new bool[10000];
	for (int i = n - 1; i >= 0; i--) {
		cache[i] = false;
	}

	int miss = 0;
	int i;
	int d;

	for (i = 0; i < n; i++) {
		d = next_arrival[i].index;
		if (!cache[d]) {
			if (Q.size() == k) {
				cache[Q.top().index] = false;
				Q.pop();
			}
			cache[d] = true;
			miss++;
		}
		else {
			k++;
		}
		Q.push(next_arrival[i]);
	}
	cout << miss;
	return 0;
}