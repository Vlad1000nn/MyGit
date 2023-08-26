/ #pragma GCC optimize("Ofast,unroll-loops")
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
    string a;

    field shift(int index) const
    {
        field ans;

        if (index == 1) ans = this->shift1();
        else if (index == 2) ans = this->shift2();
        else if (index == 3) ans = this->shift3();
        else if (index == 4) ans = this->shift4();

        return ans;
    }

    field shift1()  const
    {
        field next = *this;

        if (next.a[0] != '9')
            next.a[0] = a[0] + 1;

        return next;
    }

    field shift2()  const
    {
        field next = *this;
        if (next.a[3] != '1')
            next.a[3] = a[3] - 1;

        return next;
    }

    field shift3()  const
    {
        field next = *this;
        string buff = next.a;
        buff = next.a[3] + buff;
        buff.erase(buff.end() - 1);
        next.a = buff;

        return next;
    }

    field shift4()  const
    {
        field next = *this;
        string buff = next.a.substr(1);
        buff = buff + next.a[0];
        next.a = buff;

        return next;
    }



};


int compare(const field& a, const field& b)
{
    for (int i = 0; i < 4; ++i)
    {
        if (a.a[i] != b.a[i])
        {
            return a.a[i] - b.a[i];
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
    //  for (int i = 0; i < 4; ++i)
    in >> f.a;

    return in;
}

std::ostream& operator<<(std::ostream& out, field& f)
{
    // for (int i = 0; i < 4; ++i)
    out << f.a;

    return out;
}

void solve()
{
    field start, finish;
    cin >> start >> finish;

    std::map<field, pair<int, field>> len;
    len[start] = { 0,start };

    queue<field> q;
    q.push(start);
    while (!q.empty())
    {
        field curr = q.front();
        q.pop();

        if (curr == finish)
        {
            break;
        }

        for (int i = 1; i <= 4; ++i)
        {
            field next = curr.shift(i);
            // cout << next << ' ';
            if (len.count(next) == 0)
            {
                len[next].first = len[curr].first + 1;
                len[next].second = curr;
                q.push(next);
            }
        }

    }
    vector<string> vec;
    vec.push_back(finish.a);


    if (len.count(finish) == 0)
        cout << "-1";

    field curr = finish;
    while (!(len[curr].second == start))
    {
        vec.push_back(len[curr].second.a);
        curr = len[curr].second;
    }
    vec.push_back(start.a);
    reverse(vec.begin(), vec.end());
    for (auto& it : vec)
        cout << it << '\n';
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