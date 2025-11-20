#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
 
int main()
{
   // freopen("INPUT.TXT", "r", stdin);
   // freopen("OUTPUT.TXT", "w", stdout);
 
 
    int dp[1002]{};
    int n; cin >> n;
    dp[1] = 2;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + i;
    cout << dp[n];
 
 
    return 0;
}