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

const ll MOD = 1000000000 + 7;



bool dfs(unordered_map<string, vector<string>>& m, string v, unordered_map<string, int>& visit, bool ans, string start)
{
    visit[v] += 1;
    if (v == start)
    {
        if (visit[v] > 1)
            return false;
    }

    if (visit[v] > 1)
        return ans;

    for (auto& it : m[v])
    {
        if (!dfs(m, it, visit, ans, start))
            return false;
    }

    return true;
}

void solve()
{
    int n; cin >> n;

    unordered_map<string, vector<string>> m;
    vector<string> vec(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> vec[i];
        int size; cin >> size;
        for (int j = 0; j < size; ++j)
        {
            string s1; cin >> s1;
            m[vec[i]].push_back(s1);
        }
        string buff; cin >> buff;
        assert(buff == "*****");
    }

    for (int i = 0; i < n; ++i)
    {
        bool buff = 1;
        unordered_map<string, int> visit;
        if (!dfs(m, vec[i], visit, buff, vec[i]))
        {
            cout << "YES\n";
        }
        else cout << "NO\n";
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