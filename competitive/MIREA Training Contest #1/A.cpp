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

void solve()
{
    int n; cin >> n;
    vll vec(n); cin >> vec;
    sort(all(vec));
    ll answ{};
    for (int i = 0, j = n - 1; i < j; ++i, --j)
        answ += (vec[i] + vec[j]) * (vec[i] + vec[j]);
    
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
