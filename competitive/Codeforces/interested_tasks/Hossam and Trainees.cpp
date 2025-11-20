// https://codeforces.com/problemset/problem/1771/C?locale=en

#include <iostream>
#include <cstdio>
#include "stdio.h"
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <string_view>

#include <chrono>
#include <ctime>
#include <random>

#include <list>
#include <array>
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

#include <fstream>
#include <sstream>

//#pragma GCC optimize("Ofast,unroll-loops")
//#include <bits/stdc++.h>
//#pragma GCC target("avx,avx2,fma")


#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define debug(x) cout << #x << " = " << (x) << endl

using namespace std;
using ll = long long;
using vll = vector<long long>;
using vi = vector<int>;
using vvi = vector<vi>;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;

std::vector<int> Eratosphene(int n)
{
    std::vector<int> primes(n + 1, 1);
    primes[0] = primes[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (primes[i])
        {
            for (int j = 1ll * i * i; j <= n; j += i)
                primes[j] = 0;
        }
    }
    std::vector<int> answ;
    for (int i = 0; i <= n; ++i)
        if (primes[i])
            answ.push_back(i);
    return answ;
}


array<int, 31630> divs;
vi primes = Eratosphene(31630);

void factorize(int x, map<int,int>& cnt) {

    const int last = upper_bound(all(primes), (int)sqrt(x)) - primes.begin();

    for (int idx = 0; idx <= last; ++idx) {
        if (x % primes[idx] == 0) {
            while (x % primes[idx] == 0)
                x /= primes[idx];
            ++divs[primes[idx]];
        }
    }
    if (x > 1) {
        if (x > 31630)
            cnt[x]++;
        else
            divs[x]++;

    }
}

void solve()
{
    map<int, int> cnt;
    divs.fill(0);
    
    int n; cin >> n;
    vi a(n); cin >> a;
    for (auto& x : a)
        factorize(x, cnt);

    int ans = 0;
    for (int i = 0; i < 31630; ++i)
        ans += (divs[i] > 1);

    if (ans) {
        cout << "YES\n"; return;
    }

    for (auto& [k, v] : cnt)
        ans += (v > 1);
    
    cout << (ans ? "YES\n" : "NO\n");

}


int32_t main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    std::cin >> t;
   
    while (t--) {
        solve();
    }

    return 0;
}