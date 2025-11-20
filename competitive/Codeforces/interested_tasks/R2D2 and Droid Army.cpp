// https://codeforces.com/contest/514/problem/D?locale=en

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

struct minQ {

    stack<pair<int, int>> s1, s2;

    void add(int val) {
        s1.empty() ? s1.push(make_pair(val, val)) : s1.push(make_pair(val, max(val, s1.top().second)));
    }

    int pop() {
        if (s2.empty()) {
            if (s1.empty()) return -1;

            int v = s1.top().first;
            s2.push(make_pair(v, v));
            s1.pop();

            while (!s1.empty()) {
                int val = s1.top().first;
                s1.pop();
                s2.push(make_pair(val, max(val, s2.top().second)));
            }
        }
        int res = s2.top().first;
        s2.pop();
        return res;
    }

    int get() {
        if (s1.empty() && s2.empty()) return -1;

        if (s1.empty() || s2.empty())
            return (s1.empty() ? s2.top().second : s1.top().second);
        else
            return max(s1.top().second, s2.top().second);
    }

    void clear() {
        while (!s1.empty())
            s1.pop();
        while (!s2.empty())
            s2.pop();
    }

};

void solve()
{
    int n, m, k; cin >> n >> m >> k;

    vvi matr(n, vi(m));
    for (auto& it : matr)
        cin >> it;

    int l{}, r{};

    vi ans(n);
    vector<minQ> vals(m);
    
    int r_prev = -1;
    for (; l < n; ++l) {
        while (r < n) {
            if(r_prev != r)
                for (int i = 0; i < m; ++i)
                    vals[i].add(matr[r][i]);

            int need = 0;
            for (int i = 0; i < m; ++i)
                need += vals[i].get();
            if (need > k)
                break;
            ++r;
        }
        ans[l] = r - 1;
        for (int i = 0; i < m; ++i)
            vals[i].pop();
        r_prev = r;
    }

    for (int i = 0; i < m; ++i)
        vals[i].clear();

    int idx = -1;
    int max_ans = -1;
    for (int i = 0; i < n; ++i) {
        if (max_ans < (ans[i] - i + 1)) {
            max_ans = ans[i] - i + 1;
            idx = i;
        }
    }

    l = idx, r = ans[idx];
    for (int i = l; i <= r; ++i) {
        for (int j = 0; j < m; ++j)
            vals[j].add(matr[i][j]);
    }

    for (int i = 0; i < m; ++i) {
        cout << (vals[i].get() == -1 ? 0 : vals[i].get()) << ' ';
    }
    cout << endl;

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
