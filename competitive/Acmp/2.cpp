#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int n, n1;
    long long sum = 0;
    cin >> n;
    n1 = n;
    if (n == 0)
    {
        cout << 1;
        return 0;
    }
    if (n < 0)
        n = -n;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    if (n1 < 0)
        cout << 1 - sum;
    else
        cout << sum;
    fclose(stdin);
    fclose(stdout);
    return 0;
}