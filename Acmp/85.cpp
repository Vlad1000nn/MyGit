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

    int a, b;
    cin >> a >> b;
    int z = gcd(a, b);
    for (int i = 0; i < z; i++)
        cout << 1;

    return 0;
}