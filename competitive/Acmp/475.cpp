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

    int a;
    vector<int> vec;
    while (cin >> a)
    {
        vec.push_back(a);
    }
    sort(vec.begin(), vec.end());
    int d = vec[1] - vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] - vec[i - 1] != d)
        {
            cout << "No";
            return 0;
        }

    }
    cout << "Yes";

    return 0;
}