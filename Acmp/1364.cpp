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



struct state
{
    int a;
    int b;

    friend std::ostream& operator<<(std::ostream& out, const state& a);

    state shift(int index, int A, int B) const
    {
        state next = *this;
        if (index == 1) next = shift1(A, B);
        else if (index == 2) next = shift2(A, B);
        else if (index == 3) next = shift3(A, B);
        else if (index == 4) next = shift4(A, B);
        else if (index == 5) next = shift5(A, B);
        else if (index == 6) next = shift6(A, B);

        return next;
    }

    state shift1(int A, int B) const
    {
        state next = *this;
        next.a = A;

        return next;
    }

    state shift2(int A, int B) const
    {
        state next = *this;
        next.b = B;

        return next;
    }

    state shift3(int A, int B) const
    {
        state next = *this;
        next.a = 0;

        return next;
    }

    state shift4(int A, int B) const
    {
        state next = *this;
        next.b = 0;

        return next;
    }

    state shift5(int A, int B) const
    {
        state next = *this;
        int curr = min(B - next.b, next.a);
        next.b += curr;
        next.a -= curr;

        return next;
    }

    state shift6(int A, int B) const
    {
        state next = *this;
        int curr = min(A - next.a, next.b);
        next.a += curr;
        next.b -= curr;

        return next;
    }



};

std::ostream& operator<<(std::ostream& out, const state& a)
{
    out << a.a << ' ' << a.b;
    return out;
}

bool operator<(const state& a, const state& b)
{
    return (min(a.a, a.b) < min(b.a, b.b));
}

bool operator==(const state& a, const state& b)
{
    return (a.a == b.a) && (a.b == b.b);
}

template<>
struct std::hash<state>
{
    std::size_t operator()(state const& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(to_string(s.a));
        std::size_t h2 = std::hash<std::string>{}(to_string(s.b));
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

string strocka[6] =
{
    ">A",
    ">B",
    "A>",
    "B>",
    "A>B",
    "B>A"
};

void solve()
{
    int A, B, N; cin >> A >> B >> N;

    std::unordered_map<state, pair<state, int>> step;
    state finish{ INF,INF };

    queue<state> q;
    q.push({ 0,0 });

    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();


        if (curr.a == N || curr.b == N)
        {
            finish = curr;
            break;
        }


        for (int i = 1; i <= 6; ++i)
        {
            state next = curr.shift(i, A, B);

            if (step.count(next) == 0)
            {
                step[next] = { curr,i };
                q.push(next);
            }
        }

    }

    if (finish.a == INF)
    {
        cout << "Impossible";
        return;
    }

    vector<string> ans;
    vector<state> vec;

    state empty{ 0,0 };
    state curr = finish;
    while (!(curr == empty))
    {
        if (step[curr].second)
        {
            ans.push_back(strocka[step[curr].second - 1]);
            vec.push_back(curr);
        }
        curr = step[curr].first;
    }
    reverse(ans.begin(), ans.end());

    for (auto& it : ans)
        cout << it << '\n';

    //for (auto& it : vec)
    //    cout << it << '\n';
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