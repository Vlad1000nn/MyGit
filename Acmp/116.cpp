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
 
 
void setmax(auto& l, const auto& r)
{
    if (r > l)
        l = r;
}
 
void setmin(auto& l, const auto& r)
{
    if (r < l)
        l = r;
}
 
class SD
{
private:
 
    int gsize;
    vi a;
    vi s;
 
    void buildG(int g)
    {
        const int start = g * gsize;
        const int end = min(isz(a), start + gsize);
 
        for (int i = start; i < end; ++i)
            setmin(s[g], a[i]);
    }
 
public:
 
    SD()
    {
        ;
    }
 
    void build(const vi& vec)
    {
        a = vec;
        const int n = isz(a);
        gsize = (int)ceil(sqrt(n / 2.0));
        const int nG = n / gsize + 1;
        s.assign(nG, INT_MAX);
        for (int g = 0; g < nG; ++g)
            buildG(g);
    }
 
    int left_query(int index)
    {
        const int currg = index / gsize;
        int answ{};
 
        for (int i = index; i >= max(0, currg * gsize); --i)
        {
            if (a[i] < a[index])
                return answ;
            else ++answ;
        }
        if (!currg)
            return answ;
 
        for (int g = currg - 1; g > 0; --g)
        {
            if (s[g] < a[index])
            {
                for (int i = g * gsize + gsize - 1; i >= max(0, g * gsize); --i)
                {
                    if (a[i] < a[index])
                        return answ;
                    else ++answ;
                }
                break;
            }
            else answ += gsize;
        }
 
        for (int i = gsize - 1; i > -1; --i)
        {
            if (a[i] < a[index])
                return answ;
            else ++answ;
        }
 
        return answ;
    }
 
    int right_query(int index)
    {
        const int currg = index / gsize;
        int answ{};
 
        for (int i = index; i < min(isz(a), currg * gsize + gsize); ++i)
        {
            if (a[i] < a[index])
                return answ;
            else ++answ;
        }
        if (currg == isz(s) - 1)
            return answ;
 
        for (int g = currg + 1; g < isz(s) - 1; ++g)
        {
            if (s[g] < a[index])
            {
                for (int i = g * gsize; i < min(isz(a), g * gsize + gsize); ++i)
                {
                    if (a[i] < a[index])
                        return answ;
                    else ++answ;
                }
                break;
            }
            else answ += gsize;
        }
 
        for (int i = (isz(s) - 1) * gsize; i < min(isz(a), (isz(s) - 1) * gsize + gsize); ++i)
        {
            if (a[i] <  a[index])
                return answ;
            else ++answ;
        }
 
        return answ;
    }
 
};
 
void solve()
{
    int n, m; cin >> n >> m;
 
    vector<vector<char>> field(n, vector<char>(m));
 
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> field[i][j];
 
    vvi height(n, vi(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            height[i][j] = field[i][j] == '1';
 
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < m; ++j)
            height[i][j] = (field[i][j] == '1') * (height[i - 1][j] + 1);
    vvi dpR(n, vi(m)), dpL(n, vi(m));
 
 
    SD sd;
    for (int i = 0; i < n; ++i)
    {
        sd.build(height[i]);
        for (int j = 0; j < m; ++j)
        {
            if (field[i][j] == '1')
            {
                dpR[i][j] = sd.right_query(j);
                dpL[i][j] = sd.left_query(j);
            }
        }
    }
     
 
 
    clog << "Height:\n";
    for (auto& it : height)
    {
        for (auto& it2 : it)
            clog << it2 << ' ';
        clog << '\n';
    }
 
    clog << "dpR:\n";
    for (auto& it : dpR)
    {
        for (auto& it2 : it)
            clog << it2 << ' ';
        clog << '\n';
    }
 
    clog << "dpL:\n";
    for (auto& it : dpL)
    {
        for (auto& it2 : it)
            clog << it2 << ' ';
        clog << '\n';
    }
 
 
 
    int answ{};
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            setmax(answ, height[i][j] * (dpR[i][j] + dpL[i][j] - 1));
    }
 
    cout << answ;
 
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