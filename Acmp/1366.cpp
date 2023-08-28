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
    int n, m, s_x, s_y, f_x, f_y; cin >> n >> m;
    vector<vector<char>> field(n, vector<char>(m));

    string s; getline(cin, s);
    vector<string> vec(n);
    for (int i = 0; i < n; ++i)
        getline(cin, vec[i]);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            field[i][j] = vec[i][j];
            if (field[i][j] == 'S')
            {
                s_x = i;
                s_y = j;
                field[i][j] = ' ';
            }
            else if (field[i][j] == 'F')
            {
                f_x = i;
                f_y = j;
                field[i][j] = ' ';
            }
        }

    }

    // 0 - Вверх, 1 - Вправо, 2 - Вниз, 3 -  Влево
    vvvi dist2(4, vvi(n, vi(m, INF)));
    vvvi dist(4, vvi(n, vi(m, INF)));
    std::deque<tuple<int, int, int, int, int>> dq;
    for (int i = 0; i < 4; ++i)
        dq.push_back({ 0,0,i,s_x,s_y });
    while (!dq.empty())
    {
        auto [currDist, currDist2, dir, row, col] = dq.front();
        dq.pop_front();

        if (field[row][col] == 'X') continue;
        if (dist[dir][row][col] <= currDist) continue;

        dist2[dir][row][col] = currDist2;
        dist[dir][row][col] = currDist;

        dq.push_front({ currDist + 1,currDist2,dir, row + N[dir][0],col + N[dir][1] });
        dq.push_back({ currDist + 1,currDist2 + 1,(dir + 1) % 4, row + N[(dir + 1) % 4][0], col + N[(dir + 1) % 4][1] });
    }
    int ans = INF;
    for (int i = 0; i < 4; ++i)
        ans = min(ans, dist[i][f_x][f_y]);
    cout << (ans == INF ? -1 : ans);
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