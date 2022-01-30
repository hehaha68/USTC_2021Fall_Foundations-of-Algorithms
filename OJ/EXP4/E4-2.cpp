/*
题目：
现有N个任务需要在一台机器上进行调度，其中每个任务有相应的到达时间$r_i$和执行时间$p_i$。
任务必须在到达之后才能进行执行，该机器同时只能执行一个任务。当一个任务在机器上执行$p_i$
时间后，该任务即视为完成。若该任务的完成时刻为$f_i$，则该任务的响应时间为$f_i - r_i + 1$。
我们需要找到一个调度方案使所有任务的响应时间之和最短。需要说明的是，在这个问题里我们假设
已经将时间划分为若干不可再分的时隙，即一个任务最少的执行时间为1个单位时间，且任务只会在整
数时刻到达。
此外，调度是可抢占的，这意味着在任意时隙开始时可以通过挂起正在执行的任务i转而执行另一项任
务j，随后可以恢复任务i并执行其剩余的工作。

输入：第一行一个整数N表示总共的任务个数。
接下来的N行，每行两个整数$r_i,p_i$表示任务的到达时间和执行时间。

输出：输出一个整数表示最小的所有任务的总响应时间。
*/

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

struct task{
    int r, p;

    bool operator<(const task that) const{
        if (this->p == that.p)
            return this->r < that.r;
        else
            return this->p < that.p;
    }

    bool operator>(const task that) const{
        if (this->p == that.p)
            return this->r > that.r;
        else
            return this->p > that.p;
    }
} Task[100001];

int cmp(const task& x, const task& y){
    if (x.r == y.r)
        return x.p < y.p;
    else
        return x.r < y.r;
}

int main(){
    int n, i, sum_time = 0, time_interval;
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d %d", &Task[i].r, &Task[i].p);


    sort(Task, Task + n, cmp);

    priority_queue<task, vector<task>, greater<task>> Queue;
    Queue.push(Task[0]);
    for (i = 1; i < n; i++){
        task now = Queue.top(); // 当前任务
        Queue.pop();
        time_interval = Task[i].r - Task[i - 1].r;
        while (now.p <= time_interval){        // 下一个任务到达前完成当前任务
            sum_time += Task[i].r - time_interval + now.p - now.r;
            time_interval -= now.p;
            now.p = 0;
            if (Queue.empty())
                break;
            else{
                now = Queue.top(); // 当前执行的任务
                Queue.pop();
            }
        }

        now.p -= time_interval;
        if (now.p > 0)
            Queue.push(now);
        Queue.push(Task[i]);
    }
    int last_time = Task[n - 1].r;
    while (!Queue.empty()){
        task now = Queue.top();
        Queue.pop();
        sum_time += last_time + now.p - now.r;
        last_time += now.p;
    }
    printf("%d", sum_time);
    return 0;
}