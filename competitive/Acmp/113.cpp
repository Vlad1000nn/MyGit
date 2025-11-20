#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
 
int main()
{
    int n; cin >> n;
    vector<string> s(n);
 
    for (int i = 0; i < n; ++i)
        cin >> s[i];
 
    int N[1001][1001]{};
    int dp[1001][1001]{};
    int ans{};
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            N[i][j] = s[i][j] - '0';
        }
    }
 
    /*for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << N[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';*/
 
    for (int i = 0; i < n; ++i)
    {
        dp[0][i] = N[0][i];
        dp[i][0] = N[i][0];
        ans = max({ ans, dp[0][i], dp[i][0] });
    }
 
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (N[i][j])
            {
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
                ans = std::max(ans, dp[i][j]);
            }
        }
    }
 
  /*  for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';*/
 
    cout << ans * ans;
 
 
 
    return 0;
}