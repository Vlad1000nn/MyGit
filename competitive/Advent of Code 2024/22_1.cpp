#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

void mix(ll& secret_number, const ll& value)
{
    secret_number ^= value;
}

void prune(ll& secret_number)
{
    secret_number %= 16777216;
}

void gen_next_number(ll& secret_number)
{
    ll value = secret_number * 64;
    mix(secret_number, value);
    prune(secret_number);
    value = secret_number / 32;
    mix(secret_number, value);
    prune(secret_number);
    value = secret_number * 2048;
    mix(secret_number, value);
    prune(secret_number);
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    std::vector<ll> secret_numbers;

    // До 2000 легко, просто смоделируем
    while (getline(fin, line))
        secret_numbers.push_back(stoll(line));

    for (auto& secret_number : secret_numbers)
    {
        for (int i = 0; i < 2000; ++i)
            gen_next_number(secret_number);
    }

    ll answ = accumulate(all(secret_numbers), 0ll);
    cout << answ << '\n';
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
 
    while (t--)
        solve();

    return 0;
}
