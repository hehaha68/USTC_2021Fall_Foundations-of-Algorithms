#include<iostream>
using namespace std;
int n, m;
/*
void ppp(int** A) {
	int i, j;
	for ( i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cout << A[i][j]<<' ';
		}
		cout << '\n';
	}
}
*/
int main() {
	cin.tie(0);
	int i, j;
	cin >> n >> m;
	int** A = (int**)malloc((n + 1) * sizeof(int*));
	for (i = 0; i < n + 1; i++) { A[i] = (int*)malloc((m + 1) * sizeof(int)); }
	for (i = 0; i < n + 1; i++) { A[i][0] = 0; }
	for (i = 0; i < m + 1; i++) { A[0][i] = 0; }
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> A[i][j];
		}
	}
	//cout << '\n';
	//ppp(A);
	int result = 0;
	int** dp = (int**)malloc((n + 1) * sizeof(int*));
	for (i = 0; i < n + 1; i++) { dp[i] = (int*)malloc((m + 1) * sizeof(int)); }
	for (i = 0; i < n + 1; i++) {
		for (j = 0; j < m + 1; j++) {
			dp[i][j] = 0;
		}
	}
	//cout << '\n';
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (A[i][j] == 0) {
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
				result += dp[i][j];
			}
		}
	}
	//ppp(dp);
	cout << result << endl;

	return 0;
}
