#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


void normalization(string& s1, string& s2)
{
    while (s1.size() < s2.size())
        s1 = '0' + s1;
    while (s2.size() < s1.size())
        s2 = '0' + s2;
}


void sum(string& s1, string& s2, string& ans)
{
    normalization(s1, s2);
    normalization(ans, s1);

    for (int i = s1.size() - 1; i > 0; i--)
    {
        ans[i] += ((s1[i] - '0') + (s2[i] - '0'));
        if (ans[i] - '0' > 9)
        {
            ans[i - 1] += (ans[i] - '0') / 10;
            ans[i] = ((ans[i] - '0') % 10) + '0';
        }
    }
    if (ans[0] - '0' + (s1[0] - '0') + (s2[0] - '0') > 9)
    {
        int buff = ans[0] - '0';
        ans[0] = ((buff + (s1[0] - '0') + (s2[0] - '0')) % 10) + '0';
        ans = to_string(((s1[0] - '0') + (s2[0] - '0') + buff) / 10) + ans;
    }
    else
        ans[0] = ans[0] + (s1[0] - '0') + (s2[0] - '0');
}

int main()
{
    string s1, s2, ans;

    cin >> s1 >> s2;
    sum(s1, s2, ans);
    cout << ans;
    return 0;
}