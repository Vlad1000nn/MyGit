#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);

const ll MOD = 1000000000 + 7;

////////////////////////////////////////////////////////////////////////////////////

ll func(ll n, ll k, ll prev)
{
    // prev это предыдущий, необходимо, чтобы выполнялось условие
    // xk-1 <= xk
    
    if (!n || !k)
        return 0;
    if (k == 1)
        return n > 0;

    ll answ{};

    for (ll i = 1; i <= k; ++i)
        if (n % i == 0 && n / i <= prev)
            answ += func(n - n / i, k - 1, n / i);
    return answ;
}

void solve()
{
    // xk >= n / k
    // Сколько делителей который меньше xk? n/1, n/2, .., n/k
    // Рекурсивно перебираем их и добавляем к ответу
    ll n, k; cin >> n >> k;
    ll answ = func(n, k, n);
    answ %= MOD;
    cout << answ;
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //std::cin >> t;


	//stress();
    while (t--)
        solve();

    return 0;
}