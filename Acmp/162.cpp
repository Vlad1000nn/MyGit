
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

#include <map>
#include <queue>
#include <cassert>
#include <algorithm>
#include <functional>

#include <fstream>
#include <sstream>


#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

void solve()
{
    int n, m; cin >> n >> m;
    cout << n * (m + 1) + m * (n + 1) + m + n - 2 * (n == 1 || m == 1 || !(n % 2 == 0 || m % 2 == 0));
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //cin >> t;
    
    
    while (t--)
        solve();

    return 0;
}