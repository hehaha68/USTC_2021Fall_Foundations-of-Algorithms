# -*- coding: utf-8 -*-
""" 
题目：
勤奋的小明为了预习下学期的数据库课程，决定亲自实现一个简单的数据库系统。该数据库系统需要处理
用户的数据库插入和查询语句，并输出相应的输出。具体来说，用户的输入共包含若干条插入语句和查询
语句。其中每条插入语句包含一个主键（唯一标识）id和一个字符串s_{id}，表示在数据库中插入一个
主键为id，属性值为s_{id}的条目。每条查询语句包含一个字符串k，表示在数据库总查询是否有条目
属性值为k，若存在属性值为k的条目，则输出该条目对应的主键（输入保证至多有一个条目满足要求），
否则输出一个-1表示不存在这样的条目。

输入：首先是若干行插入语句，每行的格式为：
INSERT id s_{id}
紧接着若干行查询语句，每行的格式为：
FIND k
最后单独的一行EXIT表示输入结束。
插入语句和查询语句分别不超过10^5条，0≤id≤10^9，s_{id},k的长度不超过9。

输出：对每条查询语句输出一行，每行输出一个数字，表示查询的结果。
若存在满足条件的条目，则输出该条目的主键，否则该行输出一个−1表示没有满足条件的条目。

例子：
Input:
INSERT 1 Alice
INSERT 2 Bob
FIND Alice
FIND Bob
FIND Cindy
EXIT

Output:
1
2
-1
"""

A = {}
command = input()
while command[0] != 'E':

    if command[0] == 'I':
        _, id, sid = command.split()
        A[sid] = id

    elif command[0] == 'F':
        _, sid = command.split()
        if A.get(sid) != None:
            result = A[sid]
        else:
            result = -1
        print(result)

    command = input()