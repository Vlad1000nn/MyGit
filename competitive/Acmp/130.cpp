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
    char X1, X_1, X2, X_2; cin >> X_1 >> X1 >> X_2 >> X2;
    vector<vector<char>> field(12, vector<char>(12, '#'));
    for (int i = 2; i <= 9; ++i)
    {
        for (int j = 2; j <= 9; ++j)
            field[i][j] = '.';
    }

    int x1{ X1 - '0' + 1 }, y1{ X_1 - 97 + 2 }, x2{ X2 - '0' + 1 }, y2{ X_2 - 97 + 2 };
    //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';


    vvi dist1(12, vi(12)), dist2;
    dist2 = dist1;
    vector<vector<bool>> visit1(12, vector<bool>(12)), visit2;
    visit2 = visit1;

    queue<tuple<int, int, int, int>> q;
    q.push({ x1,y1 , 1, 0 });
    q.push({ x2,y2 , 2, 0 });
    while (!q.empty())
    {
        auto [row, col, num, currDist] = q.front();
        q.pop();

        if (field[row][col] == '#') continue;

        if (num == 1)
        {
            if (visit1[row][col])
                continue;
            visit1[row][col] = 1;
            dist1[row][col] = currDist;
        }
        else
        {
            if (visit2[row][col])
                continue;
            visit2[row][col] = 1;
            dist2[row][col] = currDist;
        }

        for (int i = 0; i < 8; ++i)
        {
            q.push({ row + Konb[i][0],col + Konb[i][1], num, currDist + 1 });
        }

    }
    int min_ans{ INT_MAX };

    for (int i = 2; i <= 9; ++i)
    {
        for (int j = 2; j <= 9; ++j)
        {
            if (visit1[i][j] && visit2[i][j] && dist1[i][j] == dist2[i][j])
            {
                min_ans = min(min_ans, dist1[i][j]);
            }
        }
    }

    /* for (int i = 2; i <= 9; ++i)
     {
         for (int j = 2; j <= 9; ++j)
         {
             cout << dist1[i][j];
         }
         cout << '\n';
     }*/


    cout << (min_ans == INT_MAX ? -1 : min_ans);






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