//#pragma GCC optimize("trapv")


#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>

#include <chrono>
#include <ctime>
#include <random>

#include <list>
#include <string>
#include <vector>
#include <bitset>
#include <set>
#include <queue>
#include <deque>
#include <map>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include <map>
#include <queue>
#include <cassert>
#include <algorithm>
#include <functional>

#include <fstream>
#include <sstream>
/*
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,fma")
*/

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

template<typename T>
using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;

template<typename T>
using MAP = map<T, T, greater<T>>;

template<typename T>
using SET = set<T, T, greater<T>>;

template<typename T>
using MULTISET = multiset<T, T, greater<T>>;



using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

namespace Random
{
    std::mt19937 mt{ std::random_device{}() };

    int get(int min, int max)
    {
        std::uniform_int_distribution<> die{ min, max };
        return die(mt);
    }
}


class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<Clock> m_beg{ Clock::now() };
public:

    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};


template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for (auto& it : vec)
        out << it << ' ';

    return out;
}


ll binpow(ll a, ll n)
{
    if (!n) return 1;

    ll res{ 1 };
    while (n)
    {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}


ll binpow(ll a, ll n, ll mod)
{
    if (!n) return 1;

    ll res = 1 % mod;
    while (n)
    {
        if (n & 1)
        {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;

    }

    return res % mod;
}


// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);

const ll MOD = 1000000000 + 7;

const int UNDEF = -1;
////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


int get_bit(const int& x, int index)
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

const ll module = 998244353;


std::vector<ll> getDividers(const ll y)
{
    std::set<ll> setansw;
    for (ll i = 1; i * i <= y; ++i)
    {
        if (y % i == 0) {
            setansw.insert(i);
            setansw.insert(y / i);
        }
    }
    std::vector<ll> answ(setansw.begin(), setansw.end());
    return answ;
}


void solve()
{
    int n, m; cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for (auto& [w, u, v] : edges)
        cin >> u >> v >> w;
    sort(all(edges));

    int l{ -1 }, r{ m + 1 }, mid;
    while (r - l > 1)
    {
        int mid = (r + l) >> 1;

        vvi graph(n + 1);
        for (int i = 0; i <= mid; ++i)
        {
            int u = get<1>(edges[i]);
            int v = get<2>(edges[i]);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vi color(n + 1, -1);
        bool good = true;
        for (int i = 1; i <= n; ++i)
        {
            if (color[i] == -1)
            {
                color[i] = 1;
                vi q = { i };
                for (int j = 0; j < isz(q); ++j)
                {
                    for (int v : graph[q[j]])
                    {
                        if (color[v] == color[q[j]])
                        {
                            good = false;
                        }
                        else if(color[v] == -1)
                        {
                            color[v] = 1 - color[q[j]];
                            q.push_back(v);
                        }
                    }
                }
            }
        }
        if (!good)
            r = mid;
        else l = mid;
        
    }
    std::cout << get<0>(edges[r]);

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //std::cin >> t;

    while (t--)
        solve();

    return 0;
}