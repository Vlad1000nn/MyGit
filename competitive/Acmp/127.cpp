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
 
#include <string>
#include <vector>
#include <bitset>
#include <set>
#include <queue>
#include <deque>
#include <map>
#include <stack>
 
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
 
 
 
//ll binpow(ll a, ll n)
//{
//    if (!n) return 1;
//
//    ll res{ 1 };
//    while (n)
//    {
//        if (n & 1)
//            res *= a;
//        a *= a;
//        n >>= 1;
//    }
//    return res;
//}
//
//ll binpow(ll a, ll n, ll mod)
//{
//    if (!n) return 1;
//
//    ll res = 1 % mod;
//    while (n)
//    {
//        if (n & 1)
//        {
//            res *= a;
//            res %= mod;
//        }
//        a *= a;
//        a %= mod;
//        n >>= 1;
//        
//    }
//
//    return res % mod;
//}
//
 
 
// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};
 
const int INF = int(1e9);
 
 
void solve()
{
    int n; cin >> n;
    vvi graph(n, vi(n));
    for (int i = 0; i < n; ++i)
        for (auto& it : graph[i]) cin >> it;
    int s, t; cin >> s >> t;
 
    vi dist(n + 1,INF);
 
    queue<pair<int, int>> q;
    q.push({ s,0 });
 
    while (!q.empty())
    {
        auto [curr, currDist] = q.front();
        q.pop();
 
        if (dist[curr] <= currDist) continue;
 
        dist[curr] = currDist;
 
        for (int i = 0; i < n; ++i)
        {
            if (graph[curr-1][i])
                q.push({ i + 1, currDist + 1 });
        }
    }
    cout << (dist[t] == INF ? -1 : dist[t]);
 
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