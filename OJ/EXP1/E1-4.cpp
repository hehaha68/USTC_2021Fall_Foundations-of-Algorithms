/*
题目：现有n个学生排成一个固定队伍进行军训，教官小明有一份所有n个人的名单
（不同的人可能重名）。小明想要在整个队伍中找到一个连续的子队伍，并且满足
该子队的所有人恰好有k个不重复的名字。请帮小明计算一下一共有多少种可能的子队伍。

输入：一共有两行，第一行有两个数字n和k，用空格分隔第二行有n个单词name_i​
，用空格分隔。输入保证len(name_i​)≤5（即输入的名字最多只含有5个字符）。
0<k<n≤10,000,000。

输出：输出一共一个数字，即可能的子队伍数量。

例子：
Input：
5 2
yyyyy iiiii yyyyy iiiii sssss
Output：
7
*/

#include <stdio.h>
#include <stdlib.h>

// Hush表用于map字符串
int hash(char* str){
    int hash = 0;
    while (*str) {
        hash = hash * 27 + (int)(*str) - 0x60;
        str++;
    }
    return hash;
}

int H[10000000] = { 0 }, win1[15000000] = { 0 }, win2[15000000] = { 0 };

int main() {
    int n, k, i, high;
    int num1 = 0,num2 = 0,mid = 0, low = 0, sum = 0;
    char *p;
    scanf("%d %d", &n, &k);
    p = (char*)malloc((n+1) * sizeof(char));
    for (i = 0; i < n; i++) {
        scanf("%s", p);
        H[i] = hash(p);
    }
    // 滑动窗口
    for (high = 0; high < n; high++) {
        if (win1[H[high]] == 0)
            num1++;
        win1[H[high]]++;

        if (win2[H[high]] == 0)
            num2++;
        win2[H[high]]++;

        while (num1 > k)
            if (--win1[H[low++]] == 0)
                num1--;
        while (num2 > k - 1)
            if (--win2[H[mid++]] == 0)
                num2--;
        if (num1 == k)  sum += mid - low;
    }
    printf("%d", sum);
    free(p);
    return 0;
}