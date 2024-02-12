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


// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
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

void dfs()
{

}

void solve()
{
    int n, m; cin >> n >> m;
    int s_x, s_y, f_x, f_y;
    vpii vec;
    vector<vector<char>> field(n + 2, vector<char>(m + 2, '#'));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> field[i][j];
            if (field[i][j] == 'C')
            {
                s_x = i;
                s_y = j;
            }
            if (field[i][j] == 'S')
            {
                f_x = i;
                f_y = j;
            }
        }
    }


    // 0-вверх, 1 - вправо, 2- вниз, 3 - влево
    // <jetpack(off/on), dir, row, col, currDist>
    deque<tuple<int, int, int, int, int>> dq;

    for (int i = 0; i < 4; ++i)
        dq.push_front({ 0, i, s_x, s_y, 0 });

    vector<vector<vector<vector<int>>>> dist(2, vector<vector<vector<int>>>(4, vvi(n + 2, vi(m + 2, INF))));
    while (!dq.empty())
    {
        auto [jetpack, dir, row, col, currDist] = dq.front();
        dq.pop_front();

        if (field[row][col] == '#') continue;
        if (dist[jetpack][dir][row][col] <= currDist) continue;
        dist[jetpack][dir][row][col] = currDist;

        // Если не было джетпака
        if (!jetpack)
        {
            // И мы его нашли
            if (field[row][col] == 'R')
            {
                // Летим дальше без потерь
                dq.push_front({ 1, dir, row + N[dir][0], col + N[dir][1], currDist });

                // Поворачиваем налево и направо
                dq.push_back({ 1, (dir + 1) % 4, row + N[(dir + 1) % 4][0], col + N[(dir + 1) % 4][1], currDist + 1 });
                dq.push_back({ 1, (dir + 3) % 4, row + N[(dir + 3) % 4][0], col + N[(dir + 3) % 4][1], currDist + 1 });
                // И в обратном
                dq.push_back({ 1, (dir + 2) % 4, row + N[(dir + 2) % 4][0], col + N[(dir + 2) % 4][1], currDist + 2 });
            }
            // Если не нашли то двигаемся в 3 направлениях дальше
            else
            {
                // Прямо
                dq.push_back({ 0, dir, row + N[dir][0], col + N[dir][1], currDist + 1 });
                // Право лево
                dq.push_back({ 0, (dir + 1) % 4, row + N[(dir + 1) % 4][0], col + N[(dir + 1) % 4][1], currDist + 1 });
                dq.push_back({ 0, (dir + 3) % 4, row + N[(dir + 3) % 4][0], col + N[(dir + 3) % 4][1], currDist + 1 });
            }
        }
        // Если же джетпак был надет
        else {
            // Летим вперед без потерь
            dq.push_front({1, dir, row + N[dir][0], col + N[dir][1], currDist });

            // Поворачиваем
            dq.push_back({ 1, (dir + 1) % 4, row + N[(dir + 1) % 4][0], col + N[(dir + 1) % 4][1], currDist + 1 });
            dq.push_back({ 1, (dir + 3) % 4, row + N[(dir + 3) % 4][0], col + N[(dir + 3) % 4][1], currDist + 1 });
        }

    }

    int ans = INF;
    ans = min({ dist[0][0][f_x][f_y], dist[0][1][f_x][f_y], dist[0][2][f_x][f_y], dist[0][3][f_x][f_y],
                dist[1][0][f_x][f_y], dist[1][1][f_x][f_y], dist[1][2][f_x][f_y], dist[1][3][f_x][f_y] });
    cout << (ans == INF ? -1 : ans);
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