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
    bool f1{}, f2{}, f3{}, f4{};

    string s; cin >> s;
    for (auto& it : s)
    {
        if (it >= 65 && it <= 90)
            f2 = true;
        if (it >= 97 && it <= 122)
            f1 = true;
        if (it - '0' >= 0 && it - '0' <= 9)
            f4 = true;
    }
    f3 = isz(s) >= 12;

    cout << (f1 && f2 && f3 && f4 ? "Yes" : "No");
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