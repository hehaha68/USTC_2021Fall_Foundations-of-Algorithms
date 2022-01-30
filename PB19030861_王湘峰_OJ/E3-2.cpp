#include <iostream>
#include <vector>

using namespace std;
vector<int> Length;

int Compute()
{
    int k = Length.size() - 2;
    for (int i = 0; i < Length.size() - 2; i++)
    {
        if (Length[i] <= Length[i + 2])
        {
            k = i;
            break;
        }
    }
    int time = Length[k] + Length[k + 1];
    Length.erase(Length.begin() + k);
    Length.erase(Length.begin() + k);
    int index;
    for (index = k - 1; index >= 0 && Length[index] <= time; --index);
    Length.insert(Length.begin() + index + 1, time);
    return time;
}

int main()
{
    cin.tie(0);
    int result = 0;
    int n;
    cin >> n;
    int length;
    for (int i = 0; i < n; i++)
    {
        cin >> length;
        Length.push_back(length);
    }
    for (int i = 0; i < n - 1; i++) // 进行n - 1次归并
        result += Compute();
    cout << result;
    return 0;
}
