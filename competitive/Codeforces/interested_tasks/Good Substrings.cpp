// https://codeforces.com/contest/271/problem/D?locale=en

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
using vvll = vector<vll>;

using ull = unsigned long long;

using vi = vector<int>;
using vvi = vector<vi>;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}


const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);

const ll mod = 998244353;
const ll MOD = 1000000000 + 7;

const int UNDEF = -1;
////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;

int base = Random::get(mod / 2, mod - 2);
vi pows1, pows2;
std::vector<int> hashes1, hashes2;

void create_hash(const string& s) {

    const int n = isz(s);
    pows1.resize(n + 1);
    pows2.resize(n + 1);
    pows1[0] = pows2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pows1[i] = pows1[i - 1] * 1ll * base % mod;
        pows2[i] = pows2[i - 1] * 1ll * base % MOD;

    }
    hashes1.resize(n + 1);
    hashes2.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
        hashes1[i] = (hashes1[i - 1] * 1ll * base + s[i - 1]) % mod;
        hashes2[i] = (hashes2[i - 1] * 1ll * base + s[i - 1]) % MOD;
    }
}

int get_hash1(int i, int j) {
    return ((hashes1[j + 1] - hashes1[i] * 1ll * pows1[j - i + 1]) % mod + mod) % mod;
}

int get_hash2(int i, int j) {
    return ((hashes2[j + 1] - hashes2[i] * 1ll * pows2[j - i + 1]) % MOD + MOD) % MOD;
}

void solve()
{
    string s, good; int k;
    cin >> s >> good >> k;
    const int n = isz(s);

    vi is_good(n);
    for (int i = 0; i < n; ++i)
        is_good[i] = good[s[i] - 'a'] - '0';

    vi pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + !is_good[i - 1];
    }

    create_hash(s);

    vpii ans;

    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (pref[r + 1] - pref[l] <= k) {
                ans.push_back(make_pair(get_hash1(l, r), get_hash2(l, r)));
            }
        }
    }

    sort(all(ans));
    cout << unique(all(ans)) - ans.begin();
}
int32_t main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--) {
        solve();
    }

    return 0;
}
