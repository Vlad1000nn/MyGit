#include <iostream>
#include <cmath>
#include <cstdlib>

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


void solve(int n)
{
    //cout << "\nNew\n";
    for (int i = 1; i < n; i++)
    {
        if (isSimple(i + n))
        {
            if (i != 1)
                solve(i - 1);
            for (int g = 0; g <= floor((n - i) / 2); g++)
            {
                cout << i + g << ' ' << n - g << '\n';
            }
            break;
        }
    }
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int n;
    cin >> n;

    solve(n);

    return 0;
}