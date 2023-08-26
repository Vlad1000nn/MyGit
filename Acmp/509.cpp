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

struct field
{
    char a[2][4];

    field shift(int di, int dj) const
    {
        field next = *this;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 4; ++j)
                if (a[i][j] == '#')
                {
                    if (i + di >= 0 && i + di < 2 && j + dj >= 0 && j + dj < 4)
                    {
                        std::swap(next.a[i][j], next.a[i + di][j + dj]);
                    }
                }
        return next;
    }
};


int compare(const field& a, const field& b)
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (a.a[i][j] != b.a[i][j])
            {
                return a.a[i][j] - b.a[i][j];
            }
        }
    }
    return 0;
}

bool operator<(const field& a, const field& b)
{
    return compare(a, b) < 0;
}

bool operator==(field& a, field& b)
{
    return compare(a, b) == 0;
}


std::istream& operator>>(std::istream& in, field& f)
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 4; ++j)
            in >> f.a[i][j];
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, field& f)
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            out << f.a[i][j];
        }
        out << '\n';
    }

    return out;
}

void solve()
{
    field start, finish;
    cin >> start >> finish;

    std::map<field, int> len;
    len[start] = 0;

    queue<field> q;
    q.push(start);
    while (!q.empty())
    {
        field curr = q.front();
        q.pop();

        if (curr == finish)
        {
            std::cout << len[curr];
            return;
        }

        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                if (i * i + j * j == 1)
                {
                    field next = curr.shift(i, j);
                    if (len.count(next) == 0) {
                        len[next] = len[curr] + 1;
                        q.push(next);
                    }
                }
            }
        }
    }

    std::cout << "-1";

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