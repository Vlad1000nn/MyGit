// https://codeforces.com/contest/185/problem/A?locale=en


﻿#include <iostream>
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
using ull = unsigned long long;
using vi = vector<int>;

const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);

const ll mod = 998244353;
const ll MOD = 1000000000 + 7;


struct matr {
    ll a, b, c, d;

    matr operator*(const matr& x) {
        matr ans(0, 0, 0, 0);
        ans.a = a * x.a + b * x.c;
        ans.b = a * x.b + b * x.d;
        ans.c = c * x.a + d * x.c;
        ans.d = c * x.b + d * x.d;

        return ans;
    }

    matr& operator%=(const ll x) {
        a %= x;
        b %= x;
        c %= x;
        d %= x;
        return *this;
    }

    matr& operator=(const matr& x) {
        a = x.a;
        b = x.b;
        c = x.c;
        d = x.d;
        return *this;
    }

};

matr binpow(matr a, ll n, ll mod)
{
    if (!n) return matr(1, 0, 0, 1);

    matr res = matr(1, 0, 0, 1);
    while (n)
    {
        if (n & 1)
        {
            res = res * a;
            res %= mod;
        }
        a = a * a;
        a %= mod;
        n >>= 1;

    }

    res %= mod;
    return res ;
}



void solve()
{
    matr start = matr(3, 1, 1, 3);

    ll n; cin >> n;
    start = binpow(start, n, MOD);

    cout << start.a << '\n';

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
