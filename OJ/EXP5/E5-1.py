"""
题目：
沙漠上，新建了N座城市，用1,2,3,...,N表示，城市与城市之间还没有道路，现在需要建设这些城市的道路网络，
需要在城市间修建道路。施工队给出了M条道路的预计费用信息，每条道路的预计费用信息可以表示为$U_i$  $V_i$ $W_i$
（即如果要在$U_i$和$V_i$之间修建道路，预计费用为$W_i$），道路是双向的。现从M条道路中选择一定数量的
道路来修建，使得这些城市之间两两之间可达（可以通过其他城市间接到达），你需要求出达成上述条件的最少预算。

输入：第1行为2个整数N、M，表示城市数量和施工队给出的M条道路的预计费用信息
接下来的M行，每行描述一条道路的预计费用信息，形式为$U_i$$V_i$$W_i$，表示如果要在$U_i$和$V_i$之间修建道路，预计费用为$W_i$

输出：输出一个数字，表示使得所有城市连通的最少预算
"""


def if_ring(x):
    if x != Parent[x]:
        Parent[x] = if_ring(Parent[x])
    return Parent[x]


N, M = input().split()
N, M = int(N), int(M)
L = [[0, 0, 0]] * M
Parent = [0] * (N + 1)
for i in range(M):
    u, v, w = input().split()
    L[i] = [int(u), int(v), int(w)]
for i in range(1, N):
    Parent[i] = i
L.sort(key=lambda x: x[2])
edge_num = 0
w_num = 0
for i in range(M):
    flag_u, flag_v = if_ring(L[i][0]), if_ring(L[i][1])
    if flag_u == flag_v:
        continue
    edge_num += 1
    w_num += L[i][2]
    Parent[flag_v] = flag_u
    if edge_num == N-1:
        break
print(w_num)