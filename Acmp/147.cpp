#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n <= 2)
        return 1;
    else
        return fibonacci(n - 2) + fibonacci(n - 1);
}
int main()
{
    //freopen("INPUT.TXT", "r", stdin);
    //freopen("OUTPUT.TXT", "w", stdout);
    int n;
    cin >> n;
    cout << fibonacci(n);

    return 0;
}