#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <string_view>
#include <iomanip>
#include <vector>
#include <utility>
#include <cstdio>
#include <bitset>

using namespace std;

int main()
{
    constexpr int length = 2000000 + 2;
    int* ptr1 = new int[length] {};
    int n;
    cin >> n;
    int N[200001];
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
        ptr1[int(N[i] + 1000000)]++;
    }
    int max_i = { 0 };
    int max_count = { 0 };

    for (int i = 0; i < length - 1; i++)
    {
        if (ptr1[i] > max_count)
        {
            max_i = i - 1000000;
            max_count = ptr1[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (N[i] == max_i)
            N[i] = -2000000;
    }
    for (int i = 0; i < n; i++)
    {
        if (N[i] != -2000000)
            cout << N[i] << ' ';
    }
    for (int i = 0; i < max_count; i++)
        cout << max_i << ' ';


    return 0;
}