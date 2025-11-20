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
    long long n, m;
    cin >> n >> m;
    if (m % n == 0)
    {
        cout << 1;
    }
    else
    {
        cout << lcm(n, m) / m;
    }

    return 0;
}