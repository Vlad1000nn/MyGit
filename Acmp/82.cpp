#include <iostream>
#include <cmath>
#include <algorithm>


using namespace std;


int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    int N[100001] = { 0 };
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        N[x] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        int y;
        cin >> y;
        if (N[y] == 1)
            N[y] = 2;
    }
    for (int i = 0; i < 100001; i++)
    {
        if (N[i] == 2)
            cout << i << ' ';
    }

    return 0;
}