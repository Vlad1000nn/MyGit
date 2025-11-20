#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int a, b;
    cin >> a >> b;
    cout << lcm(a, b);
    return 0;
}