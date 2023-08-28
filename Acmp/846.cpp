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
    int n, m, f_x, f_y, L; cin >> n >> m;
    vector<vector<char>> field(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            cin >> field[i][j];
    }

    cin >> f_x >> f_y >> L; --f_x; --f_y;
    int coords[4][3];
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
            cin >> coords[i][j];
    }

    vvvi dist(4, vvi(n, vi(m, INF)));
    queue<tuple<int, int, int, int>> q;
    for (int i = 0; i < 4; ++i)
        q.push({ i,coords[i][0] - 1,coords[i][1] - 1,0 });

    while (!q.empty())
    {
        auto [dir, row, col, currDist] = q.front();
        q.pop();

        if (field[row][col] == '1') continue;
        if (dist[dir][row][col] <= currDist) continue;

        dist[dir][row][col] = currDist;

        for (int i = 0; i < 4; ++i)
            q.push({ dir,row + N[i][0],col + N[i][1],currDist + 1 });
    }
    int ans = 0;
    for (int i = 0; i < 4; ++i)
    {
        ans += coords[i][2] * (dist[i][f_x][f_y] <= L);
    }
    cout << ans;


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