#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>

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

bool is_perfect(long long n)
{
    if (n == 1 || n == 2)
        return false;

    long long sum = { 0 };
    for (long long i = n / 2; i > 0; i--)
    {
        if (sum > n)
            return false;
        if (n % i == 0)
            sum += i;
    }
    //  cout << sum;
    return (sum == n) ? true : false;
}



int main()
{
    //freopen("INPUT.TXT", "r", stdin);
    //freopen("OUTPUT.TXT", "w", stdout);

    // cin.tie(0);                  //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ІСЏ� ·� єСѓ cin � є cout
   //  std::ios_base::sync_with_stdio(false);    //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ё� ЅС…СЂ� ѕ� Ѕ� ё� ·� °С� � ёСЋ cout/cin � ё print/scanf

    long long n, m;
    cin >> n >> m;
    bool flag = { false };
    vector<long long> vec;

    for (int i = 2; i < 35; i++)
    {
        if (isSimple(i))
        {
            long long x = pow(2, i - 1) * (pow(2, i) - 1);
            //   cout << x << ' ';
            vec.push_back(x);
        }
    }
    if (n % 2 != 0 && n != m)
        n += 1;

    for (int i = 0; i < vec.size(); i++)
    {
        if (i == 4 || i == 8 || i == 9)
            continue;
        if (vec[i] >= n && vec[i] <= m)
        {
            cout << vec[i] << '\n';
            flag = true;
        }
    }

    if (!flag)
        cout << "Absent";


    return 0;
}