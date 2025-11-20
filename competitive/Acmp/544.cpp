#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <bitset>>
 
using namespace std;
 
using ll = long long;
 
void solve()
{
    int n; cin >> n;
    ll dp[100]{};
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 4; i <= n; ++i)
    {
        dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
    }
    cout << dp[n];
 
}
 
 
int main()
{
     
    int t{ 1 };
    //cin >> t;
    while (t--)
        solve();
 
    return 0;
}