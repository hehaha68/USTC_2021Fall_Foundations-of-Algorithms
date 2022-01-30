#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 10001
using namespace std;

int dp[MAX];//�洢��󱳰�����ܴ����
int value[MAX], weight[MAX], number[MAX];//�ֱ�������Ʒ�ļ�ֵ��ÿһ���������Լ�����
int bag;

void ZeroOnePack(int weight, int value)//01����
{
    int i;
    for (i = bag; i >= weight; i--)
    {
        dp[i] = max(dp[i], dp[i - weight] + value);
    }
}
void CompletePack(int weight, int value)//��ȫ����
{
    int i;
    for (i = weight; i <= bag; i++)
    {
        dp[i] = max(dp[i], dp[i - weight] + value);
    }
}

void MultiplePack(int weight, int value, int number)//���ر���
{
    if (bag <= number * weight)//����������������Ʒ������ҪС����ô�����Ʒ����ֱ��ȡ�꣬�൱����ȫ����
    {
        CompletePack(weight, value);
        return;
    }
    else//����ͽ����ر���ת��Ϊ01����
    {
        int k = 1;
        while (k <= number)
        {
            ZeroOnePack(k * weight, k * value);
            number = number - k;
            k = 2 * k;//������ö�����˼��
        }
        ZeroOnePack(number * weight, number * value);
    }
}
int main()
{
    int n;
    cin >> n >> bag;
    int i, sum = 0;
    for (i = 0; i < n; i++)
    {
        cin >> weight[i];//��������
        cin >> value[i];//�����ֵ
        cin >> number[i];//��������
    }
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < n; i++)
    {
        MultiplePack(weight[i], value[i], number[i]);//���ö��ر���,ע�⴩�ε�ʱ��ֱ�����������ֵ������
    }
    cout << dp[bag] << endl;
    return 0;
}
