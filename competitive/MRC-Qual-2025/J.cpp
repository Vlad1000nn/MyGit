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
using vll = vector<long long>;
using vvll = vector<vll>;

using vi = vector<int>;
using vvi = vector<vi>;

class DSU {
private:

    vi parent, sz;
    

    int getParent(const int x)  
    {
        return (parent[x] == x ? x : parent[x] = getParent(parent[x]));
    }

public:

    DSU(const int n)
        : parent(n)
        , sz(n, 1)
    { 
        std::iota(all(parent), 0);
    }

    bool merge(int x, int y)
    {
        x = getParent(x);
        y = getParent(y);

        if (x == y)
            return false;

        if (sz[x] < sz[y])
            swap(x, y);
        
        sz[x] += sz[y];
        parent[y] = x;
        return true;
    }
    

};


void solve() {

    while (true) {
        int n, m, l, r;
        cin >> n >> m >> l >> r;
        if (!n && !m && !l && !r) return;

        DSU dsu1(n), dsu2(n);
        
        vvll edges(m, vll(3)); 
        vvll edges2(m, vll(3));

        for (ll i = 0,u,v, a,b; i < m; ++i)
        {
            cin >> u >> v >> a >> b;
            --u; --v;
            edges[i][0] = edges2[i][0] = u;
            edges[i][1] = edges2[i][1] = v;
            edges[i][2] = a + b * l;
            edges2[i][2] = a + b * r;

        }
        
        sort(all(edges), [&](const auto& x, const auto& y) {
            return x[2] < y[2];
            });

        sort(all(edges2), [&](const auto& x, const auto& y) {
            return x[2] < y[2];
            });

        ll sum1 = 0;
        ll sum2 = 0;
        for (int i = 0; i < m; ++i)
            sum1 += dsu1.merge(edges[i][0], edges[i][1]) * edges[i][2];

        for (int i = 0; i < m; ++i)
            sum2 += dsu2.merge(edges2[i][0], edges2[i][1]) * edges2[i][2];

        cout << min(sum1, sum2) << '\n';

    }
}


int32_t main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
