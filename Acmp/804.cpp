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


//ll binsearch(ll l, ll r, bool(*f)(ll))
//{
//    while (l != r)
//    {
//        ll mid = (r + l + 1) >> 1;
//        cout << mid << '\n';
//        if (f(mid))
//            r = mid - 1;
//        else l = mid;
//    }
//    return l;
//}
//
//
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





void solve()
{
    constexpr int INF = int(1e9);
    int n, m; cin >> n >> m;

    int T_x, T_y;

    vector<vector<char>> field(n, vector<char>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> field[i][j];
            if (field[i][j] == 'T')
            {
                T_x = i;
                T_y = j;
                field[i][j] = '.';
            }
        }
    }


    vvi dist(n, vi(m, INF));

    int N[4][2] =
    {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    };

    queue<tuple<int, int, int>> q;
    q.push({ n - 2, m - 2, 0 });
    while (!q.empty())
    {
        auto [x, y, curr_dist] = q.front();
        q.pop();

        if (field[x][y] == '#' || x < 1 || x > n - 2) continue;

        if (dist[x][y] <= curr_dist) continue;

        dist[x][y] = curr_dist;
        for (int i = 0; i < 4; ++i)
            q.push({ x + N[i][0],y + N[i][1],curr_dist + 1 });

    }




    cout << dist[1][1] << '\n' << (dist[1][1] < dist[T_x][T_y] ? "Yes" : "No");

}

void mysolve()
{
    constexpr int INF = int(1e9);

    int n, m; cin >> n >> m;

    int T_x, T_y;

    vector<vector<char>> field(n, vector<char>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> field[i][j];
            if (field[i][j] == 'T')
            {
                T_x = i;
                T_y = j;
                field[i][j] = '.';
            }
        }
    }

    vvi dist(n, vi(m, INF));

    queue<tuple<int, int, int>> q;

    q.push({ n - 2, m - 2,0 });

    int N[4][2] = {
        {-1,0},{1,0}, {0,1},{0,-1}
    };

    while (!q.empty())
    {
        auto [x, y, currDist] = q.front();
        q.pop();

        if (field[x][y] == '#' || x < 1 || x > n - 2) continue;

        if (dist[x][y] <= currDist) continue;

        dist[x][y] = currDist;
        for (int i = 0; i < 4; ++i)
            q.push({ x + N[i][0], y + N[i][1], currDist + 1 });

    }

    cout << dist[1][1] << '\n' << (dist[1][1] < dist[T_x][T_y] ? "Yes" : "No");


}



int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);


    int t{ 1 };
    //cin >> t;
    while (t--)
        mysolve();

    return 0;
}