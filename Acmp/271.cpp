#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int N[100000];

void is_fibonacci(int n)
{
    int k = 2;
    while (N[k] < n)
    {
        N[k + 1] = N[k] + N[k - 1];
        k++;
    }
    if (N[k] == n)
    {
        cout << 1 << '\n' << k;
    }
    else
        cout << 0;
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int n;
    N[1] = N[2] = 1;
    cin >> n;
    is_fibonacci(n);


    return 0;
}