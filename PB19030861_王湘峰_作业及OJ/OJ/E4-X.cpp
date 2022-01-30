#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int* X = new int[n];
    for (int i = 0; i < n; i++)
        cin >> X[i];
    sort(X, X + n);
    int low = 0, high = X[n - 1] - X[0];
    int target = n - m;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int last = X[0];
        int cloth = 1;

        for (int i = 1; i < n; i++)
        {
            if (X[i] >= last + mid)
            {
                cloth++;
                last = X[i];
            }
        }
        if (cloth < target) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << high;
    return 0;
}