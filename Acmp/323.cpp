#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

using namespace std;


bool isSimple(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int n;
    cin >> n;
    for (int i = 2; i < n; i++)
    {
        int x = n - i;
        bool a = { isSimple(x) && isSimple(i) };
        if (a)
        {
            cout << min(x, i) << ' ' << max(x, i);
            return 0;
        }
    }

    return 0;
}