#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    int n, R;
    cin >> n >> R;
    int* X = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> X[i];
    }
    sort(X, X + n);
    int start = X[0];
    int counter = 0;
    int center = -R - 1;

    for (int i = 1; i < n; i++)
    {
        for (; (start >= X[i] - R) && i < n; i++);
        counter++;
        center = X[i - 1];
        for (; (X[i] <= center + R) && i < n; i++);
        start = X[i];
    }
    if (X[n - 1] > center + R)
        counter++;
    cout << counter;
}