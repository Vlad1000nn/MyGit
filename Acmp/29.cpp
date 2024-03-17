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
 
 
// Р СџР ВµРЎР‚Р ВµР В±Р С•РЎР‚ Р Р…Р В°Р С—РЎР‚Р В°Р Р†Р В»Р ВµР Р…Р С‘Р в„–
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
 
 
 
//#define int ll
 
int func(pair<int, int>& first, pair<int, int>& second)
{
    auto [age1, secret1] = first;
    auto [age2, secret2] = second;
    return (age1 > age2 ? secret1 : secret2);
}
 
void setmin(auto& x, auto y)
{
    if (x > y)
        x = y;
}
 
void solve()
{
    int n; cin >> n;
    vi vec(n); cin >> vec;
    vi dp(n);
    dp[0] = 0;
    dp[1] = abs(vec[1] - vec[0]);
 
    for (int i = 2; i < n; ++i)
    {
        dp[i] = min(dp[i - 1] + abs(vec[i] - vec[i - 1]), dp[i - 2] + 3 * (abs(vec[i] - vec[i - 2])));
    }
     
    cout << dp[n - 1];
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