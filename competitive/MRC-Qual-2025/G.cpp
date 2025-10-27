#include <iostream>
#include <cstdio>
#include "stdio.h"
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cstring>

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

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

bool str_comp(const string& s, int l1, int r1, int l2, int r2) {
    const int n = r1 - l1 + 1;
    const int m = r2 - l2 + 1;
    if (n != m)
        return n < m;
    return memcmp(s.c_str() + l1, s.c_str() + l2, n) < 0;
}

bool str_comp(const string& s1, int l, int r, const string& s2) {
    const int n = r - l + 1;
    const int m = isz(s2);
    if (n != m)
        return n < m;

    return memcmp(s1.c_str() + l, s2.c_str(), n) < 0;
}

void solve()
{
    string s; cin >> s;
    const int n = isz(s);
    int k = 0;
    while (k * (k - 1) / 2 <= n)++k;
    k = min(n, k);

    if (n == 1) {
        cout << s << '\n';
        return;
    }

    vvi dp1(n, vi(k + 1));
    vvi dp2(n, vi(k + 1));
    vvi pref_dp1(n + 1, vi(k + 1));
    vvi suff_dp2(n + 1, vi(k + 1));

    pref_dp1[0][0] = 1;
    suff_dp2[n][0] = 1;
    for (int i = 1; i <= k; ++i) {
        pref_dp1[0][i] = pref_dp1[0][i - 1] + 1;
        suff_dp2[n][i] = suff_dp2[n][i - 1] + 1;
    }

    for (int i = 1; i <= k; ++i) {
        dp1[i - 1][i] = 1;
        dp2[n - i][i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        int last_j = 1;
        for (int j = 1; j <= k; ++j) {
            last_j = j;
            if (i - j < 0) break;

            if (pref_dp1[i - j][j - 1] > 0) {
                dp1[i - 1][j] = 1;
            }
            else if (i - 2 * j >= 0) {
                int l1 = i - 2 * j;
                int r1 = i - j - 1;
                int l2 = i - j;
                int r2 = i - 1;
                if (dp1[i - j - 1][j] && str_comp(s, l1, r1, l2, r2))
                    dp1[i - 1][j] = 1;
            }
            pref_dp1[i][j] = pref_dp1[i][j - 1] + dp1[i - 1][j];

        }
        while (last_j <= k) {
            pref_dp1[i][last_j] = pref_dp1[i][last_j - 1];
            last_j++;
        }
    }

    for (int i = n; i >= 1; --i) {
        int last_j = 1;
        for (int j = 1; j <= k; ++j) {
            last_j = j;
            if (i + j - 1 > n) break;

            if (suff_dp2[i + j - 1][j - 1] > 0) {
                dp2[i - 1][j] = 1;
            }
            else if (i + 2 * j <= n) {
                int l1 = i + j - 1;
                int r1 = i + 2 * j - 2;
                int l2 = i - 1;
                int r2 = i + j - 2;
                if (dp2[i + j - 1][j] && str_comp(s, l1, r1, l2, r2))
                    dp2[i - 1][j] = 1;
            }
            suff_dp2[i - 1][j] = suff_dp2[i - 1][j - 1] + dp2[i - 1][j];
        }
        while (last_j <= k) {
            suff_dp2[i - 1][last_j] = suff_dp2[i - 1][last_j - 1];
            last_j++;
        }
    }

    string ans = std::string(n + 2, '9');

    for (int i = 1; i <= k; ++i) {
        if (dp1[n - 1][i] && str_comp(s, n - i, n - 1, ans))
            ans = s.substr(n - i, i);
    }

    for (int i = 1; i <= k; ++i) {
        if (dp2[0][i] && str_comp(s, 0, i - 1, ans))
             ans = s.substr(0, i);
    }

    cout << ans << '\n';
}

int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--) {
        solve();
    }

    return 0;
}
