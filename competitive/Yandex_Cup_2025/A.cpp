#include <iostream>
#include <cstdio>
#include "stdio.h"
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cstring>

#include <chrono>
#include <ctime>
#include <random>

#include <list>
#include <array>
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
#include <functional>

#include <fstream>
#include <sstream>

//#pragma GCC optimize("Ofast,unroll-loops")
//#include <bits/stdc++.h>
//#pragma GCC target("avx,avx2,fma")


#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define debug(x) cout << #x << " = " << (x) << endl

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

const ll mod = 998244353;
const ll MOD = 1000000000 + 7;

const int UNDEF = -1;
////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


int get_bit(const ll& x, ll index)
{
    return (x >> index) & 1;
}
/*/
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
/*/

std::vector<ll> Eratosphene(ll n)
{
    std::vector<int> primes(n + 1, 1);
    primes[0] = primes[1] = 0;
    for (ll i = 2; i <= n; ++i)
    {
        if (primes[i])
        {
            for (ll j = 1ll * i * i; j <= n; j += i)
                primes[j] = 0;
        }
    }
    std::vector<ll> answ;
    for (ll i = 0; i <= n; ++i)
        if (primes[i])
            answ.push_back(i);
    return answ;
}

const long double pi = 3.14159265358979323846;

struct xorshift32_state {
    uint32_t a;
};

/* The state must be initialized to non-zero */
uint32_t xorshift32(struct xorshift32_state* state)
{
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    uint32_t x = state->a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return state->a = x;
}

void solve()
{
    int n, m; cin >> n >> m;

    int k = sqrt(n + m);
    if (k * k != n + m || (!n && !m)) {
        cout << "NO\n"; return;
    }

    if (k % 2 == 1) {
        cout << "YES\n"; return;
    }
    else {
        if (n % 2 == 0 && m % 2 == 0) {
            cout << "YES\n"; 
        }
        else
            cout << "NO\n";
    }



}


int32_t main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
