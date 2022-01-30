/*
��Ŀ��
����N��������Ҫ��һ̨�����Ͻ��е��ȣ�����ÿ����������Ӧ�ĵ���ʱ��$r_i$��ִ��ʱ��$p_i$��
��������ڵ���֮����ܽ���ִ�У��û���ͬʱֻ��ִ��һ�����񡣵�һ�������ڻ�����ִ��$p_i$
ʱ��󣬸�������Ϊ��ɡ�������������ʱ��Ϊ$f_i$������������Ӧʱ��Ϊ$f_i - r_i + 1$��
������Ҫ�ҵ�һ�����ȷ���ʹ�����������Ӧʱ��֮����̡���Ҫ˵�����ǣ���������������Ǽ���
�Ѿ���ʱ�仮��Ϊ���ɲ����ٷֵ�ʱ϶����һ���������ٵ�ִ��ʱ��Ϊ1����λʱ�䣬������ֻ������
��ʱ�̵��
���⣬�����ǿ���ռ�ģ�����ζ��������ʱ϶��ʼʱ����ͨ����������ִ�е�����iת��ִ����һ����
��j�������Իָ�����i��ִ����ʣ��Ĺ�����

���룺��һ��һ������N��ʾ�ܹ������������
��������N�У�ÿ����������$r_i,p_i$��ʾ����ĵ���ʱ���ִ��ʱ�䡣

��������һ��������ʾ��С���������������Ӧʱ�䡣
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
        task now = Queue.top(); // ��ǰ����
        Queue.pop();
        time_interval = Task[i].r - Task[i - 1].r;
        while (now.p <= time_interval){        // ��һ�����񵽴�ǰ��ɵ�ǰ����
            sum_time += Task[i].r - time_interval + now.p - now.r;
            time_interval -= now.p;
            now.p = 0;
            if (Queue.empty())
                break;
            else{
                now = Queue.top(); // ��ǰִ�е�����
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