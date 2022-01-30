#include<stdio.h>
#include<stdlib.h>

int main() {
    int t, num;
    int i, j, k;
    int N;
    int tag;
    scanf("%d", &t);
    for (i = 0; i < t; i++) {

        tag = 0;
        N = 0;
        scanf("%d", &num);

        int* B = (int*)malloc(num * sizeof(int));
        for (j = 0; j < num; j++) {
            scanf("%d", &k);
            if (k > N) { N = k; }
            B[j] = k;
        }

        int* A = (int*)malloc(N * sizeof(int));

        for (j = 0; j < N; j++) {
            A[j] = 0;
        }

        for (j = 0; j < num; j++) {
            A[B[j]] += 1;
        }

        for (j = 0; j < N; j++) {
            if (A[j] >= (num + 1) / 2.0) {
                printf("%d\n", j);
                tag = 1;
                break;
            }
        }

        if (tag == 0) {
            printf("-1\n");
        }

        free(A);
        free(B);

    }
    return 0;
}