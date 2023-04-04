#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <cstdio>


using namespace std;

int N[100000];

void RemoveAt(int index, int& n)
{
    for (int i = index + 1; i < n; i++)
    {
        N[i - 1] = N[i];
    }
    n--;
}

int main()
{
    cin.tie(0);                  //Отключает связку cin к cout
    std::ios_base::sync_with_stdio(false);    //Отключает синхронизацию cout/cin и print/scanf
    int n;
    cin >> n;
    int N[201]{};
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        N[x + 100]++;
    }
    for (int i = 0; i < 201; i++)
    {
        if (N[i] != 0)
        {
            for (int g = 0; g < N[i]; g++)
            {
                cout << i - 100 << ' ';
            }
        }
    }

    return 0;
}