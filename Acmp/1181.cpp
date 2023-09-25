//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimize("trapv")
//#include <bits/stdc++.h>

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

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cassert>
#include <algorithm>;
#include <functional>

using namespace std;

template<typename T>
using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;


using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;


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

//#define int ll

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


// Перебор направлений
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);
const ll INFL = ll(1e18);

class SD
{
private:

    vi a, s;
    const int gsize = 256;

    void buildG(int g)
    {
        const int start = g * gsize;
        const int end = min(start + gsize, (int)a.size());
        for (int i = start; i < end; ++i)
            s[g] += (!a[i]);
    }


public:

    SD(const vi& vec)
    {
        build(vec);
    }

    void build(const vi& vec)
    {
        a = vec;
        const int  n = (int)vec.size();
        const int nG = (n + gsize - 1) / gsize;
        s.assign(nG, 0);
        for (int g = 0; g < nG; ++g)
            buildG(g);
    }

    int get_zero_cnt(int left, int right)
    {
        int res = 0;
        int gl = left / gsize;
        int gr = right / gsize;

        if (gl == gr)
        {
            for (int i = left; i <= right; ++i)
                res += (!a[i]);
        }
        else {
            for (int g = left; g < (gl + 1) * gsize; ++g)
                res += (!a[g]);
            for (int g = gl + 1; g < gr; ++g)
                res += s[g];
            for (int g = gr * gsize; g <= right; ++g)
                res += (!a[g]);
        }

        return res;
    }

};


void solve()
{
    int n; cin >> n;
    vi vec(n);
    for (auto& it : vec)
        cin >> it;

    SD sd(vec);

    int m; cin >> m;
    for (int i = 0, x, y; i < m; ++i)
    {
        cin >> x >> y;
        cout << sd.get_zero_cnt(x - 1, y - 1) << ' ';
    }
}


int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int t{ 1 };
    //cin >> t;
    while (t--)
        solve();
    return 0;
}