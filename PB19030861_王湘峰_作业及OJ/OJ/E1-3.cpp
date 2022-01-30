#include<stdio.h>
#include<stdlib.h>

long int merge(long int* A, long int* temp, long int begin, long int mid, long int end) {
    long int i = begin;
    long int j = mid + 1;
    long int k = begin;
    long int p;
    long int num = 0;

    while (i <= mid && j <= end) {
        if (A[i] > A[j]) {
            temp[k] = A[j];
            j++;
            k++;
            num += mid - i + 1;
        }
        else {
            temp[k] = A[i];
            k++;
            i++;
        }
    }

    while (i <= mid) {
        temp[k] = A[i];
        i++;
        k++;
    }
    while (j <= end) {
        temp[k] = A[j];
        j++;
        k++;;
    }
    for (p = begin; p <= end; p++) {
        A[p] = temp[p];
    }

    return num;
}

long int merge_sort(long int* A, long int* temp, long int begin, long int end) {

    long int counter = 0;

    if (begin >= end) { return 0; }

    long int mid = (begin + end) / 2;

    counter += merge_sort(A, temp, begin, mid);
    counter += merge_sort(A, temp, mid + 1, end);
    counter += merge(A, temp, begin, mid, end);

    return counter;
}

int main() {
    long int len;
    long int t;
    long int i;

    scanf("%d", &len);
    long int* A = new long int[len];
    long int* temp = new long int[len];

    for (i = 0; i < len; i++) {
        scanf("%d", &t);
        A[i] = t;
    }

    long int counter = merge_sort(A, temp, 0, len - 1);
    printf("%d\n", counter % 10000007);

    return 0;
}
