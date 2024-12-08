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


void build_set(vector<ll>& S, const vll& vec, int l, int r, const ll& m)
{
    int n = (r - l);

    ll sum;
    for (int mask = 0; mask < (1 << n); ++mask)
    {
        sum = 0;
        for (int i = 0; i < n; ++i)
            if (get_bit(mask, i))
                sum += vec[l + i];
        S.push_back(sum % m);
    }
}

void solve()
{
    ll n, m; cin >> n >> m;
    vll vec(n); cin >> vec;
    int mid = n / 2;

    vector<ll> S1, S2;
    build_set(S1, vec, 0, mid, m);
    build_set(S2, vec, mid, n, m);
    sort(all(S1));
    sort(all(S2));

    ll answ{};
    for (auto& it : S2)
    {
        setmax(answ, (*(--S1.end()) + it) % m);
        auto need = lower_bound(all(S1), m - it);
        if(need != S1.begin())
            setmax(answ, (it + *(--need)) % m);
    }
    std::cout << answ << '\n';
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
