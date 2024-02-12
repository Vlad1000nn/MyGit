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

#include <fstream>
#include <sstream>


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


// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);

//const ll MOD = 1000000000 + 7;
const ll MOD = LLONG_MAX;

const int UNDEF = -1;
////////////////////////////////////////////////////////////////////////////////////


using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;

// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& obj)
{
    typename std::vector<T>::const_iterator i;
    for (i = obj.begin(); i != obj.end(); ++i)
        out << *i << '\n';

    return out;
}

//#define int ll


void solve()
{
    int n; cin >> n;
    vvi graph(n);
    vpii coords(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> coords[i].first >> coords[i].second;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (coords[i].first == coords[j].first || coords[i].second == coords[j].second)
                graph[i].push_back(j), graph[j].push_back(i);
        }
    }

    queue<int> q;
    vi visit(n);
    int ans{};

    while (find(all(visit), 0) != visit.end())
    {
        auto ix = find(all(visit), 0);
        int i = ix - visit.begin();
        q.push(i);

        while (!q.empty())
        {
            auto curr = q.front();
            q.pop();

            if (visit[curr]) continue;
            visit[curr] = 1;
            for (auto& it : graph[curr])
                q.push(it);
        }

        ++ans;
    }

    cout << ans - 1;

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