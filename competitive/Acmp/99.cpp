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


void solve()
{
    int h, n, m; cin >> h >> n >> m;

    int s_h, s_x, s_y;
    int f_h, f_x, f_y;

    vector<vector<vector<char>>> field(h + 1, vector<vector<char>>(n + 2, vector<char>(m + 2, '#')));

    for (int i = 0; i < h; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= m; ++k)
            {
                cin >> field[i][j][k];
                if (field[i][j][k] == '1')
                {
                    s_h = i;
                    s_x = j;
                    s_y = k;
                    field[i][j][k] = '.';
                }
                else if (field[i][j][k] == '2')
                {
                    f_h = i;
                    f_x = j;
                    f_y = k;
                    field[i][j][k] = '.';
                }
            }
        }
    }

    n += 2; m += 2;
    vvvi dist(h + 1, vvi(n, vi(m, INF)));

    std::deque<tuple<int, int, int, int>> dq;

    dq.push_back({ s_h,s_x,s_y,0 });
    while (!dq.empty())
    {
        auto [lvl, row, col, currDist] = dq.front();
        dq.pop_front();

        if (field[lvl][row][col] == 'o' || field[lvl][row][col] == '#') continue;

        if (dist[lvl][row][col] <= currDist) continue;

        dist[lvl][row][col] = currDist;

        for (int i = 0; i < 4; ++i)
        {
            dq.push_front({ lvl,row + N[i][0],col + N[i][1],currDist + 1 });
        }
        dq.push_back({ lvl + 1,row,col,currDist + 1 });

    }

    cout << dist[f_h][f_x][f_y] * 5;
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