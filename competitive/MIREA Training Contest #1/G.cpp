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


template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}


using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


int get_bit(const ll& x, ll index)
{
    return (x >> index) & 1;
}

void setmax(auto& l, const auto& r)
{
    if (r > l)
        l = r;
}

void setmin(auto& l, const auto& r)
{
    if (r < l)
        l = r;
}


void solve()
{
    ll L, R, N; cin >> L >> R >> N;
    set<ll> input;
    for (ll i = 0, x; i < N; ++i)
    {
        cin >> x;
        input.insert(x);
    }
    vll vec(all(input));

    const int cnt = isz(vec);
    ll curr{ 1 };
    int bit_cnt{};
    ll answ{};
    for (int mask = 1; mask < (1 << cnt); ++mask)
    {
        curr = 1;
        bit_cnt = 0;
        for (int i = 0; i < cnt; ++i)
            if (get_bit(mask, i)) {
                ++bit_cnt;
                if (1.0l * curr * vec[i] > 1e16)
                    curr = 1e16;
                else
                    curr *= vec[i];
            }

        ll diff = (R  / curr) - ((L - 1) / curr);

        if (bit_cnt & 1)
            answ += diff;
        else
            answ -= diff;
    }

    std::cout << answ;
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