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

using ll = long long;

using vi = vector<int>;
using vvi = vector<vi>;


bool str_comp(const string& s1, int l1, int r1, const string& s2)
{
    const int n = r1 - l1 + 1;
    const int m = isz(s2);
    if (n != m)
        return n < m;

    return memcmp(s1.c_str() + l1, s2.c_str(), n) < 0;
}

bool str_comp(const string& s, int l1, int r1, int l2, int r2)
{
    const int n = r1 - l1 + 1;
    const int m = r2 - l2 + 1;
    if (n != m)
        return n < m;

    return memcmp(s.c_str() + l1, s.c_str() + l2, n) < 0;
}

void solve()
{
    string curr, buff;
    int k = 0;
    string s; cin >> s;
    const int n = isz(s);
    if (n == 1) {
        cout << s << '\n'; return;
    }
    while (k * (k - 1) / 2 <= n)
        ++k;
    k = min(n, k);

    vvi pref_dp1(n + 1, vi(k + 1));
    vvi pref_dp2(n + 1, vi(k + 1));

    vvi dp1(n, vi(k + 1));
    vvi dp2(n, vi(k + 1));

    for (int i = 1; i <= k; ++i)
        dp1[i-1][i] = dp2[i-1][i] = 1;
     
    pref_dp1[0][0] = pref_dp2[0][k] = 1;
    for (int i = 1; i <= k; ++i)
        pref_dp1[0][i] = pref_dp1[0][i - 1] + 1;
    for (int i = 1; i <= k; ++i)
        pref_dp2[0][i] = pref_dp2[0][i - 1] + 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i - j < 0) goto pref1_up;

            if (pref_dp1[i - j][j - 1]) {
                dp1[i - 1][j] = 1;
            }
            else if (i - 2 * j >= 0) {
                int k = j;
                if (dp1[i - j - 1][k] == 1 && str_comp(s,i - j - k, i - j - 1, i - j, i - 1))
                    dp1[i - 1][j] = 1;
            }
            pref1_up:
            pref_dp1[i][j] = pref_dp1[i][j - 1] + dp1[i - 1][j];
        }
    }

    // 142857
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i - j < 0) goto pref2_up;

            if (pref_dp2[i - j][j - 1]) {
                dp2[i - 1][j] = 1;
            }
            else if (i - 2 * j >= 0) {
                int k = j;
                if (dp2[i - j - 1][k] == 1 && str_comp(s, n - i + j + k - 1, n - i + j, n - i + j - 1, n - i))
                    dp2[i - 1][j] = 1;
            }

            pref2_up:
            pref_dp2[i][j] = pref_dp2[i][j - 1] + dp2[i - 1][j];
        }
    }

    string ans = std::string(n + 2, '9');
    for (int i = 0; i <= k; ++i)
        if (dp1[n - 1][i] && str_comp(s, n - i, n - 1, ans))
            ans = s.substr(n - i, i);

    for (int i = 0; i <= k; ++i) {
        if (dp2[n - 1][i] && str_comp(s, 0, i - 1, ans))
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
