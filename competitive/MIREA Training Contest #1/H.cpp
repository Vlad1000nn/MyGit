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

const ll INFL = ll(1e18);

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


ll distance(int x1, int y1, int x2 = 0, int y2 = 0)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void solve()
{
    int sx, sy; cin >> sx >> sy;
    int n; cin >> n;
    vpii vec(n); for (auto& it : vec) cin >> it.first >> it.second;
    for (auto& [x, y] : vec)
        x -= sx, y -= sy;

    std::vector<std::tuple<ll, int, int>> dist((1 << n), { INFL, -1, -1 }); // mask, prev, next
    dist[0] = { 0, -1, -1 };
    for (int mask = 1; mask < (1 << n); ++mask)
    {
        int a = log2(mask);

        setmin(dist[mask], std::make_tuple(get<0>(dist[mask - (1 << a)]) + 2 * distance(vec[a].first, vec[a].second), a, -1));
        for (int next = 0; next < a; ++next)
            if (get_bit(mask, next))
                setmin(dist[mask], std::make_tuple(get<0>(dist[mask - (1 << a) - (1 << next)]) + distance(vec[a].first, vec[a].second)
                    + distance(vec[a].first, vec[a].second, vec[next].first, vec[next].second) + distance(vec[next].first, vec[next].second), a, next));
    }
    
    int curr = (1 << n) - 1;
    cout << get<0>(dist[curr]) << '\n';
    vector<int> answ = { 0 };
    while (curr > 0)
    {
        answ.push_back(get<1>(dist[curr]) + 1);

        if (get<2>(dist[curr]) != -1) {
            answ.push_back(get<2>(dist[curr]) + 1);
            curr -= (1 << get<2>(dist[curr]));
        }
        curr -= (1 << get<1>(dist[curr]));
        answ.push_back(0);
    }

    for (auto& it : answ)
        cout << it << ' ';
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
