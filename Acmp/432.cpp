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


// Перебор направлений
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

// Ходы коня
const int Konb[8][2] = {
    {-2, -1}, {-2, 1}, {-1, 2}, {1,2}, {2,-1},{2,1},{-1,-2},{1,-2}
};


const int INF = int(1e9);


void solve()
{
    int n, m; cin >> n >> m;
    vector<vector<char>> field(n + 2, vector<char>(m + 2, '*'));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> field[i][j];

    n += 2; m += 2;


    vi dist(1);

    vvi visit(n, vi(m));

    for (int i = 1; i < n - 1; ++i)
    {
        for (int j = 1; j < m - 1; ++j)
        {
            if (field[i][j] == '#' && !visit[i][j])
            {
                queue<tuple<int, int>> q;
                q.push({ i,j });

                while (!q.empty())
                {
                    auto [row, col] = q.front();
                    q.pop();

                    if (field[row][col] != '#') continue;
                    if (visit[row][col]) continue;

                    visit[row][col] = dist.size();
                    for (int i = 0; i < 4; ++i)
                    {
                        if (!visit[row + N[i][0]][col + N[i][1]])
                            q.push({ row + N[i][0], col + N[i][1] });
                    }
                }
                dist.push_back(1);
            }
        }
    }


    cout << dist.size() - 1;



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