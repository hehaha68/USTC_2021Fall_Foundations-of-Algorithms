#include <iostream>
#include <algorithm>
using namespace std;

typedef struct point
{
    int x;
    int y;
    bool operator<(const point b) const
    {
        return this->y < b.y;
    }
    bool operator>=(const point b) const
    {
        return this->y >= b.y;
    }
} point;

int partition(point* A, int left, int right) {
    point p = A[right];
    int i = left - 1;
    int j;
    for (j = left; j < right; j++) {
        if (A[j].x <= p.x) {
            i = i + 1;
            point t = A[i];
            A[i] = A[j];
            A[j] = t;
        }
    }
    A[right] = A[i + 1];
    A[i + 1] = p;
    return i + 1;
}
void quicksort(point* A, int left, int right) {
    if (left < right) {
        int rp = rand() % (right - left + 1) + left;
        point t = A[rp];
        A[rp] = A[right];
        A[right] = t;
        int pivot = partition(A, left, right);
        quicksort(A, left, pivot - 1);
        quicksort(A, pivot + 1, right);
    }
    return;
}

int main() {
    cin.tie(0);
    int n;
    int length = 0;
    int i;
    cin >> n;
    point* P = (point*)malloc(n * sizeof(point));
    point* F = (point*)malloc(n * sizeof(point));

    for (i = 0; i < n; i++) {
        F[i].x = -1; F[i].y = -1;
    }

    for (i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
    }

    quicksort(P, 0, n - 1);

    for (i = 0; i < n; i++) {
        if (P[i] >= F[length]) { F[++length] = P[i]; }
        else {
            *lower_bound(F + 1, F + length + 1, P[i]) = P[i];
        }
    }
    cout << length;
    return 0;
}
