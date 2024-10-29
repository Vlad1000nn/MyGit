//#pragma GCC optimize("trapv")
 
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
#include <functional>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;




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

const ll module = 998244353;


void topsort(const vvi& graph, vi& visit, vi& order, int u)
{
    if (visit[u])
        return;
    visit[u] = 1;

    for (auto& it : graph[u])
        topsort(graph, visit, order, it);
    order.push_back(u);
}

void go_backward(const vvi& graph, vi& used, map<int, vi>& css, int u, int color)
{
    if (used[u])
        return;

    used[u] = color;
    css[color].push_back(u);
    for (auto& it : graph[u])
        go_backward(graph, used, css, it, color);
}


void solve()
{
    //  Построим граф: Если в множестве с номером u есть число v, значит мы можем перейти из u в v
    //  Решением задачи будет поиск валидных вершин, в которые мы можем вернуться за какое-то количество ходов
    //  Это просто поиск КСС
    // Пусть валидных вершин k, тогла ответ 2^k - 1

    int n; cin >> n;
    vvi graph(n + 1);
    vvi inversed(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int k; cin >> k;
        while (k--)
        {
            int u; cin >> u;
            graph[i].push_back(u);
            inversed[u].push_back(i);
        }
    }

    vi order, visit(n + 1);
    int color{ 1 };
    for (int i = 1; i <= n; ++i)
    {
        if (visit[i])
            continue;
        topsort(graph, visit, order, i);
    }

    reverse(all(order));

    visit.assign(n + 1, 0);

    map<int, vi> css;
    for (int i = 0; i < n; ++i)
    {
        if (visit[order[i]])
            continue;
        go_backward(inversed, visit, css, order[i], ++color);
    }
    int k{};
    for (auto& [key, val] : css)
    {
        if (isz(val) == 1)
        {
            auto f = lower_bound(all(graph[val[0]]), val[0]);
            if (f != graph[val[0]].end() && *f == val[0])
                ++k;
        }
        else
            k += isz(val);
    }

    ll answ = binpow(2ll, k, module) - 1;
    std::cout << answ << '\n';

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    std::cin >> t;

    while (t--)
        solve();

    return 0;
}