#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

using namespace std;


bool isSimple(long long x)
{
    for (long long i = 2; i <= sqrt(x); i++)
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

    cin.tie(0);                               //Отключает связку cin к cout
    std::ios_base::sync_with_stdio(false);    //Отключает синхронизацию cout/cin и print/scanf

    long long n;
    cin >> n;
    if (!isSimple(n))
    {
        while (n % 2 == 0)
        {
            cout << 2;
            n /= 2;
            if (n != 1)
                cout << '*';

        }

        for (int i = 3; i <= sqrt(n); i += 2)
        {
            while (n % i == 0)
            {
                cout << i;
                n /= i;
                if (n != 1)
                    cout << '*';
            }
        }
        if (n != 1)
            cout << n;
    }
    else
        cout << n;
    return 0;
}