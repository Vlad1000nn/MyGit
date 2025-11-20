#include <iostream>
#include <cmath>
#include <cstdlib>
#include <numeric>

using namespace std;
long long N[1000000] = { 0 };

int fibonacci(int n)
{
    for (int i = 3; i <= n; i++)
    {
        N[i] = (N[i - 2] % 1000000000 + N[i - 1] % 1000000000) % 1000000000;
    }
    return N[n];
}

int main()
{
    cin.tie(0);                  //Отключает связку cin к cout
    std::ios_base::sync_with_stdio(false);    //Отключает синхронизацию cout/cin и print/scanf

    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    N[1] = N[2] = 1;
    int n1, n2;
    cin >> n1 >> n2;
    cout << fibonacci(gcd(n1, n2));

    return 0;
}