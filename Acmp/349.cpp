#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

using namespace std;



int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    cin.tie(0);                               //Отключает связку cin к cout
    std::ios_base::sync_with_stdio(false);    //Отключает синхронизацию cout/cin и print/scanf
    bool P[1000001];
    for (int i = 0; i < 1000001; i++)
    {
        P[i] = true;
    }
    int n, m;
    cin >> m >> n;
    for (int i = 2; i <= 1000001 / 2; i++)
    {
        for (int g = 2 * i; g < 1000001; g += i)
        {
            P[g] = false;
        }
    }

    bool f = { false };
    for (int i = m; i <= n; i++)
    {
        if (P[i])
        {
            cout << i << '\n';
            f = true;
        }
    }
    if (!f)
        cout << "Absent";

    return 0;
}