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

using vpii = vector<pair<int, int>>;


void solve()
{
    int n; cin >> n;
    vpii vec(n); 
    for (auto& it : vec)
        cin >> it.first >> it.second;
    reverse(all(vec));
    std::map<int, int> x_cnt, y_cnt;
    std::map<std::pair<int, int>, int> pair_cnt;
    ll answ{};

    for (auto& [x, y] : vec)
    {
        answ -= pair_cnt[std::make_pair(x, y)];
        answ += x_cnt[x];
        answ += y_cnt[y];
        
        pair_cnt[std::make_pair(x, y)]++;
        x_cnt[x]++;
        y_cnt[y]++;
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
