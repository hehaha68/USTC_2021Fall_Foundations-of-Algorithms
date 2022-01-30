#include <iostream>
#include <stdlib.h>
#include <string.h>
#include<map>
using namespace std;

int main()
{
    int i,n, k;
    int left = 0, right = 0;
    int typenum = 0;
    int sum = 0, duplication = 1;
    map<string, int>hash;

    cin >> n >> k;

    char** Name = (char**)malloc(n * sizeof(char*));

    for (i = 0; i < n; i++) {
        Name[i] = (char*)malloc(6 * sizeof(char));
    }

    for (right = 0; right < n; right++)
    {
        cin >> Name[right];
        if (hash.count(Name[right]) == 0) {
            hash[Name[right]] = 1;
        }
        else {
            hash[Name[right]]++;
        }
        if (hash[Name[right]] == 1)
            typenum++;
        for(;typenum>k||hash[Name[left]]>1; hash[Name[left]]--,++left)
        {
            if (hash[Name[left]] > 1)
                duplication++;
            else
            {
                duplication = 1;
                typenum--;
            }
        }
        if (typenum == k)
            sum += duplication;
    }
    printf("%d\n", sum);
    return 0;
}