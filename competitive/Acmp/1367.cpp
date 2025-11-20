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
#include <unordered_map>
#include <unordered_set>

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

// Перебор направлений
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

// Ходы коня
const int Konb[8][2] = {
    {-2, -1}, {-2, 1}, {-1, 2}, {1,2}, {2,-1},{2,1},{-1,-2},{1,-2}
};

const int Cat1[6][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}, {-1,1}, {1,1}
};

const int Cat2[6][2] = {
    {-1,0}, {0, 1}, {1,0}, {0,-1}, {-1,-1}, {1,-1}
};

const int INF = int(1e9);


string X;
int K;

struct state
{
    int short_s;            // Текущий остаток
    int len;

    state add(char c)
    {
        state next = *this;
        ++next.len;

        next.short_s = next.short_s * 10 + (c - '0');
        next.short_s %= K;

        return next;
    }

    bool isGood()
    {
        return (short_s % K == 0);
    }

};

bool operator==(const state& a, const state& b)
{
    return a.len == b.len && a.short_s == b.short_s;
}

bool operator<(const state& a, const state& b)
{
    if (a.len == b.len) return a.short_s < b.short_s;

    return a.len < b.len;
}

bool operator>(const state& a, const state& b)
{
    if (a.len == b.len) return a.short_s > b.short_s;

    return a.len > b.len;
}


void solve()
{
    int D;
    cin >> X >> K >> D;

    vi vec(D);
    for (auto& it : vec) cin >> it;
    std::sort(vec.begin(), vec.end());

    string buff; buff += X[0];

    for (int i = 1; i < X.size(); ++i)
    {
        buff += X[i];
        int x = stoi(buff);
        x %= K;
        buff = to_string(x);
    }

    bool flag = {};
    bitset<100001> bits;
    bits.reset();

    state start{ stoi(buff),0 };

    std::map<state, pair<state, char>> m;
    m[start] = { start,0 };

    queue<state> q;
    q.push(start);

    int cnt{};
    while (!q.empty() && cnt != 300000)
    {
        ++cnt;
        auto curr = q.front();
        q.pop();

        if (bits[curr.short_s]) continue;
        bits[curr.short_s] = 1;

        if (curr.isGood())
        {
            cout << X;
            vector<char> ans;
            while (m[curr].second != 0)
            {
                ans.push_back(m[curr].second);
                curr = m[curr].first;
            }
            reverse(ans.begin(), ans.end());
            for (auto& it : ans) cout << it;

            return;
        }

        for (auto& it : vec)
        {
            state next = curr.add(it + '0');
            if (m.count(next) == 0)
            {
                m[next] = { curr,it + '0' };
                q.push(next);
            }
        }

    }

    cout << "-1";


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