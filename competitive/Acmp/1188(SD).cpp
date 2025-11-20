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
#include <algorithm>;
#include <functional>


#define isz(x) (int)x.size()

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

std::istream& operator>>(std::istream& in, vi& vec)
{
    for (auto& it : vec)
        cin >> it;
    return in;
}

std::ostream& operator<<(std::ostream& in, vi& vec)
{
    for (auto& it : vec)
        cout << it << ' ';
    return in;
}


std::istream& operator>>(std::istream& in, vll& vec)
{
    for (auto& it : vec)
        cin >> it;
    return in;
}

std::ostream& operator<<(std::ostream& in, vll& vec)
{
    for (auto& it : vec)
        cout << it << ' ';
    return in;
}

//#define int ll

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


// Перебор направлений
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);
const ll INFL = ll(1e18);

const ll MOD = 1000000000 + 7;

const int UNDEF = -1;


vi stovi(string& s)
{
    vi ans(isz(s));
    const int n = isz(s);
    for (int i = 0; i < n; ++i)
        ans[i] = s[i] - '0';

    return ans;
}


class SD
{
private:

    vll a;
    //vll s;

    vector<bool> b;
    vll sum;

    const int gsize = 256;

public:

    SD(const vll& vec)
    {
        build(vec);
    }

    void print()
    {
        cout << "Print:\n";
        cout << "gsize: " << gsize << '\n';
        cout << "a: ";
        for (auto& it : a) cout << it << ' ';
        cout << "\nb: ";
        for (int i = 0; i < isz(b); ++i)
            cout << b[i] << ' ';
        cout << "\nsum: ";
        for (auto& it : sum) cout << it << ' ';
        cout << '\n';
    }

    void build(const vll& vec)
    {
        a = vec;
        const int n = isz(a);
        //gsize = (int)ceil(sqrt(n / 2.0));
        //const int nG = n / gsize + 1;
        const int nG = (n + gsize - 1) / gsize;

        //s.assign(nG, 0);
        b.assign(nG, 0);
        sum.assign(nG, 0);

        //for (int g = 0; g < nG; ++g)
        //    buildG(g);
    }


    void add(int left, int right, int value)
    {
        int gl = left / gsize;
        int gr = right / gsize;

        if (gl == gr)
        {
            for (int i = left; i <= right; ++i)
                a[i] += value;
        }
        else {
            for (int g = left; g < (gl + 1) * gsize; ++g)
                a[g] += value;

            for (int g = gl + 1; g < gr; ++g)
            {
                sum[g] += value;
                b[g] = 1;
            }

            for (int g = gr * gsize; g <= right; ++g)
                a[g] += value;
        }
    }

    ll get(int index)
    {
        const int gc = index / gsize;
        update(gc);
        return a[index];
    }

    void update(int g)
    {
        if (!b[g]) return;

        for (int i = g * gsize; i < (g + 1) * gsize; ++i)
            a[i] += sum[g];
        sum[g] = 0;
    }


};

void solve()
{
    int n; cin >> n;
    vll vec(n); cin >> vec;


    SD sd(vec);

    //sd.print();

    int q; cin >> q;
    for (int i = 0; i < q; ++i)
    {
        char c; cin >> c;
        if (c == 'a')
        {
            int l, r, value;
            cin >> l >> r >> value;
            --l; --r;
            sd.add(l, r, value);
        }
        else
        {
            int x; cin >> x;
            cout << sd.get(x - 1) << ' ';
        }
    }
    cout << '\n';
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
