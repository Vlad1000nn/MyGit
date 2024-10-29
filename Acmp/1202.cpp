
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

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cassert>
#include <algorithm>;

using namespace std;

template<typename T>
using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;


using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;



using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;




const int INF = int(1e9);
const ll INFL = ll(1e18);


void solve()
{
    int n, e; cin >> n >> e;
    vvi graph(n, vi(n));
    for (int i = 0, x, y; i < e; ++i)
    {
        cin >> x >> y;
        graph[x - 1][y - 1] = 1;
    }
    cout << n << '\n';

    for (int i = 0; i < n; ++i)
    {
        int curr = std::count(graph[i].begin(), graph[i].end(), 1);
        cout << curr << ' ';
        if (!curr) {
            cout << '\n';
            continue;
        }
        for (int j = 0; j < n; ++j)
            if (graph[i][j]) cout << j + 1 << ' ';
        cout << '\n';
    }
}



int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);


    int t{ 1 };
    //cin >> t;
    while (t--)
        solve();
    return 0;
}