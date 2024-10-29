
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
#include <algorithm>

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


void DFS(vvi& graph,vector<bool>& visit, int v)
{
    visit[v] = 1;
    for (int i = 0; i < graph.size(); ++i)
        if(!visit[i])
        DFS(graph, visit, i);

   
}

void solve()
{
    int e{};
    int n; cin >> n;
    vvi graph(n, vi(n));
    for (auto& it : graph)
        for (auto& it2 : it) {
            cin >> it2;
            if (it2 == 1) ++e;
        }
   

    cout << n << ' ' << e << '\n';

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            if (graph[i][j]) cout << i + 1 << ' ' << j + 1 << '\n';
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