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
#include <algorithm>
#include <functional>

#include <fstream>
#include <sstream>


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

void dfs(const vvi& graph, vvll& dp, int curr, int parent, const ll& low, const ll& high, const int& cnt_low, const int& cnt_high, const int& k)
{
    vll childs;
    for (auto& it : graph[curr])
    {
        // Если родитель то скип
        if (it  == parent)
            continue;
        childs.push_back(it);
        dfs(graph, dp, it, curr, low, high, cnt_low, cnt_high, k);
    }

    vll pref(isz(childs) + 1);
    const int n = isz(childs);
    
    if (n == 0) // Лист
    {
        dp[curr][0] = low;
        dp[curr][1] = high;
        return;
    }

    // Красим всех детей в дорогой
    ll start = 0;              
    for (auto& it : childs)
        start += dp[it][1];

    // Поменял детей на разницу (выбрать low - выбрать high)
    for (auto& it : childs)
        it = dp[it][0] - dp[it][1];
    sort(all(childs));
    // Сортим по возрастанию (поскольку нам нужно минимизировать)

    pref[1] = childs[0];
    for (int i = 2; i <= n; ++i) 
        pref[i] = pref[i - 1] + childs[i-1];

    dp[curr][0] = start + low;
    dp[curr][1] = start + high;

    // Считаем динамику для dp[curr][0]
    // Так как мы взяли уже low, то у нас максимум cnt_low - 1 может быть взято low
    // Ну а минимум который мы можем взять, это max(0, n - cnt_high)

    const int max_can_get_low = min(cnt_low - 1, n);  // Предел наших возможностей
    const int min_can_get_low = max(0, n - cnt_high); // Иногда мы просто вынуждены брать минимумы

    // Тут обновляем динамику
    for (int cnt = min_can_get_low; cnt <= max_can_get_low; ++cnt)
        setmin(dp[curr][0], start + low  + pref[cnt]);

    // Динамика для dp[curr][1]
    const int max_can_get_high = min(cnt_low, n); // Максимум это либо все дети, либо все наши цвета(смотря что меньше)
    const int min_can_get_high = max(0, n - cnt_high + 1); // + 1 потому что один high мы уже взяли
    // Посчитали
    for (int cnt = min_can_get_high; cnt <= max_can_get_high; ++cnt)
        setmin(dp[curr][1], start + high + pref[cnt]);
}


void solve()
{
    int n, k; cin >> n >> k;
    vvi graph(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int cntA{}, cntB{};
    vll c(k); cin >> c;
    ll high{}, low{ INF };
    for (auto& it : c)
    {
        setmax(high, it);
        setmin(low, it);
    }

    for (auto& it : c)
        (it == high ? ++cntB : ++cntA);

    vvll dp(n + 1, vll(2)); // dp[u][type] — максимальный ответ для поддерева вершины u, если u = type(0 или 1)

    dfs(graph, dp, 1,0, low, high, cntA, cntB, k);

    std::cout << min(dp[1][0], dp[1][1]) << '\n';

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
