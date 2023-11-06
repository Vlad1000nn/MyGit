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


#include <map>
#include <queue>
#include <cassert>
#include <algorithm>
#include <functional>


#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

template<typename T>
using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;
template<typename T>

using MAP = map<T, T, greater<T>>;


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

std::istream& operator>>(std::istream& in, vi& vec)
{
    for (auto& it : vec)
        cin >> it;
    return in;
}

std::ostream& operator<<(std::ostream& in, vi& vec)
{
    for (auto& it : vec)
        cout << it << ' ';
    return in;
}


std::istream& operator>>(std::istream& in, vll& vec)
{
    for (auto& it : vec)
        cin >> it;
    return in;
}

std::ostream& operator<<(std::ostream& in, vll& vec)
{
    for (auto& it : vec)
        cout << it << ' ';
    return in;
}

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
const ull INFUL = ull(1e19);

const ll MOD = 1000000000 + 7;

const int UNDEF = -1;

////////////////////////////////////////////////////////////////////////////////////

class FenwickTree
{
private:

    vll sums;
    int n;

    int f(int index)
    {
        return index & (index + 1);
    }

    ll sum(int index)
    {
        ll ans{};
        while (index >= 0)
        {
            ans += sums[index];
            index = f(index) - 1;
        }
        return ans;
    }

public:

    FenwickTree(int n)
        : n(n)
        , sums(n, 0)
    { }

    ll rsq(int left, int right)
    {
        return sum(right) - sum(left - 1);
    }

    void add(int index, int value)
    {

        while (index < n)
        {
            sums[index] += value;
            index |= index + 1;
        }
    }
};

void solve()
{
    int n, m; cin >> n >> m;
    FenwickTree f(n);

    const string ADD = "add";
    const string RSQ = "rsq";

    while (m--)
    {
        string s; cin >> s;
        int x, y; cin >> x >> y;
        if (s == ADD)
        {
            f.add(x - 1, y);
        }
        else if (s == RSQ)
        {
            cout << f.rsq(x - 1, y - 1) << '\n';
        }
        else throw 1;
    }

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //cin >> t;
    while (t--)
        solve();
    return 0;
}