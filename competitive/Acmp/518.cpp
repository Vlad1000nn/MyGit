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




void Eratosthen(vector<int>& primes, int n)
{
    vector<bool> isPrime(n + 1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
            for (int j = i * i; j <= n; j+=i)
                isPrime[j] = 0;
    }

    for (int i = 0; i < isz(isPrime); ++i)
        if (isPrime[i])
            primes.push_back(i);
}

void dp_init(vvi& prevDp, vvi& currDp, const vi& primes)
{
    for (int a = 0; a < 10; ++a)
        for (int b = 0; b < 10; ++b)
            for (int c = 0; c < 10; ++c)
            {
                int target = 100 * a + 10 * b + c;
                auto it = lower_bound(all(primes), target);
                if (it != primes.end() && target == *it)
                    currDp[b][c]  += 1;

            }
    prevDp = currDp;
    fill(all(currDp), vi(10, 0));
}

void solve1()
{
    int n; cin >> n;
    vi primes;
    Eratosthen(primes, 1000);
    if (n == 3)
    {
        cout << isz(primes);
        return;
    }

    for (auto& it : primes)
        cout << it << ' ';
    cout << '\n';

    vvi prevDp(10, vi(10));
    vvi currDp(10, vi(10));
    
    dp_init(prevDp, currDp, primes);

    cout << "start value:\n";
    for (auto& it : prevDp)
    {
        for (int i = 0; i < 10; ++i)
            cout << it[i] << ' ';
        cout << '\n';
    }
    
    for (int i = 0; i < n - 3; ++i)
    {
        for (int a = 0; a < 10; ++a)
            for (int b = 0; b < 10; ++b)
                for (int c = 0; c < 10; ++c)
                {
                    int target = 100 * a + 10 * b + c;
                    auto it = lower_bound(all(primes), target);
                    if (it != primes.end() && target == *it)
                        currDp[b][c] += prevDp[a][b];

                }
        prevDp = currDp;
        fill(all(currDp), vi(10, 0));

        cout << i << " VALUE\n";
        for (auto& it : prevDp)
        {
            for (int i = 0; i < 10; ++i)
                cout << it[i] << ' ';
            cout << '\n';
        }
    }


    ll answ{};
    for (auto& vec : prevDp)
    {
        for (auto& val : vec)
            answ += val;
    }
    cout << answ;

}


int get_bit(const int& x, int index)
{
    return (x >> index) & 1;
}

void solve()
{
    int n, k; cin >> n >> k;
    vector<vector<vector<int>>> dp(n + 2, vector<vector<int>>(n + 2, vector<int>(k + 1)));
    vector<vector<char>> field(n + 2, vector<char>(n + 2, '1'));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> field[i][j];

    dp[1][1][0] = 1;
    for (int curr = 1; curr <= k; ++curr)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                for (int x = 0; x < 4; ++x)
                    dp[i][j][curr] += (field[i + N[x][0]][j + N[x][1]] == '0') * dp[i + N[x][0]][j + N[x][1]][curr - 1];
            }
    }


    cout << dp[n][n][k];
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