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
    int k = { 0 };
    cin >> n;
    for (int i = n + 1; i < 2 * n; i++)
    {
        if (isSimple(i))
            k++;
    }
    cout << k;

    return 0;
}