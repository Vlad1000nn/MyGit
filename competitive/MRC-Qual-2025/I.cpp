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

#define int ll

int queries = 19;

void query(int x) {
    assert(queries-- > 0);
    assert(x >= 1 && x <= 65536);
    cout << "? " << x << endl;
}


void solve()
{
    queries = 19;
    int ans;

    int l = 8, r = 65536, mid;
    query(l);
    cin >> ans;
    if (ans == 0) {
        for (int i = 2; i <= 8; ++i) {
            query(i);
            cin >> ans;
            if (ans == 0)
            {
                cout << "! " << i << endl;
                return;
            }
        }
    }

    while (true) {
        mid = l * l - 1;
        if (mid > 65536) break;
        query(mid);
        cin >> ans;
        if (ans == 1)
            l = mid;
        else
        {
            r = mid + 1;
            break;
        }
    }

    while (r - l > 1) {
        mid = (r + l) >> 1;
        query(mid);
        cin >> ans;

        if (ans == 1)
            l = mid;
        else r = mid;
    }

    cout << "! " << r << endl;
}

int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
