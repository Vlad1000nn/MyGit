#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>

int N[100000] = { 0 };

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

int calculate(int n)
{
    if (n == 1)
    {
        //cout << 1 << '\n';
        return 0;
    }
    int count = { 0 };
    if (!isSimple(n))
    {
        while (n % 2 == 0)
        {
            //cout << 2 << ' ';
            count++;
            n /= 2;
        }

        for (int i = 3; i <= sqrt(n) + 5; i += 2)
        {
            while (n % i == 0)
            {
                count++;
                //cout << i << ' ';
                n /= i;
            }
        }
        if (isSimple(n) && n != 1)
            count++;
        //cout << n;
        //cout << '\n';
        return count;
    }
    else
    {
        //cout << n << '\n';
        return 1;
    }
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    //cin.tie(0);                                 //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ІСЏ� ·� єСѓ cin � є cout
    //std::ios_base::sync_with_stdio(false);    //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ё� ЅС…СЂ� ѕ� Ѕ� ё� ·� °С� � ёСЋ cout/cin � ё print/scanf

    int m, n;
    cin >> n >> m;
    int n1 = n / gcd(n, m);
    int m1 = m / gcd(n, m);
    //cout << n1 << ' ' << m1<<'\n';
    //cout << calculate(n1) << '\n' << calculate(m1) << '\n';
    int sum = { calculate(n1) + calculate(m1) };
    cout << sum;


    return 0;
}