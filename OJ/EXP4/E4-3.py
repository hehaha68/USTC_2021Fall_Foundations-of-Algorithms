"""
题目：
现有一个长为N的数据访问序列和一块大小为K的缓存，请设计算法使数据访问的MISS次数最少。
假设所有可能访问的数据在一个确定的范围内，这里用整数来表示存放数据的地址。
假设无论是否命中，这次访问的数据都需要存放在缓存内。

输入：第一行两个整数N,K表示共有N个数据访问的请求，缓存大小为K。
接下来的N行每行一个整数i，表示访问内存地址为i的数据。

输出：输出一个整数表示最少的MISS次数。
"""
T = {} # 一个值的访问时间
M = [] # 缓存
A = [] # 访问序列

n,k = input().split()
n,k = int(n), int(k)
A = [-1] * n
M = [-1] * k
for i in range(n):
    A[i] = int(input())
    if A[i] not in T.keys():
        T[A[i]] = [i]
    else:
        T[A[i]].append(i)
miss=0
for i in range(n):
    T[A[i]].pop(0)
    if A[i] not in M:
        miss += 1
        empty = [j for j, x in enumerate(M) if x == -1]
        if empty:
            M[empty[0]] = A[i]
        else:
            max = rep = -1
            for j in range(k):
                if not T[M[j]]:
                    rep = j
                    break
                if max < T[M[j]][0] - i:
                    max = T[M[j]][0] - i
                    rep = j
            M[rep] = A[i]
print(miss)
