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

void setmax(auto& l, const auto& r)
{
    if (r > l)
        l = r;
}


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

    while (getline(fin, line))
        secret_numbers.push_back(stoll(line));

    // Теперь у нас известны цены, и хранятся изменения цен
    const int n = isz(secret_numbers);
    const int m = 2000; // Количество чисел

    map<vector<int>, ll> total_change;
    vector<vector<int>> prices(n, vector<int>(m + 1));
    vector<vector<int>> changes(n, vector<int>(m + 1));
    
    for (int i = 0; i < n; ++i)
    {
        prices[i][0] = secret_numbers[i] % 10;
        for (int j = 1; j <= m; ++j) {
            gen_next_number(secret_numbers[i]);
            prices[i][j] = secret_numbers[i] % 10;
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= m; ++j)
            changes[i][j] = prices[i][j] - prices[i][j - 1];
     
    std::vector<int> curr;
    map<vector<int>, ll> curr_change;
    for (int i = 0; i < n; ++i)
    {
        curr_change.clear();
        for (int j = 4; j <= m; ++j)
        {
            curr = { changes[i][j - 3], changes[i][j - 2], changes[i][j - 1], changes[i][j] };
            if(curr_change.find(curr) == curr_change.end())
                curr_change[curr] =  prices[i][j];
        }

        for (auto& [key, val] : curr_change)
            total_change[key] += val;
    }
    ll answ{};
    for (auto& it : total_change)
        setmax(answ, it.second);
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
