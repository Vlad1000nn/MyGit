#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iomanip>

using namespace std;

int calculate1(int a)
{
    string s = to_string(abs(a));
    sort(s.begin(), s.end());

    if (s.find('0') == 0 && a < 0)//избавляемся от возможного нуля спереди
    {
        int k = 0;
        while (s[k] == '0')
            k++;
        swap(s[0], s[k]);
    }

    if (a > 0)
        reverse(s.begin(), s.end());
    return a >= 0 ? stoi(s) : -stoi(s);
}

int calculate2(int b)
{
    string s = to_string(abs(b));
    sort(s.begin(), s.end());

    if (s.find('0') == 0 && b > 0)  //избавляемся от возможного нуля спереди
    {
        int k = 0;
        while (s[k] == '0')
            k++;
        swap(s[0], s[k]);
    }
    if (b < 0)
        reverse(s.begin(), s.end());
    return b >= 0 ? stoi(s) : -stoi(s);
}


int main()
{
    //cin.tie(0);                  
    //std::ios_base::sync_with_stdio(false);    

    int a, b;
    cin >> a >> b;
    int s1 = calculate1(a);
    int s2 = calculate2(b);
    int ans = max(s1, a) - min(s2, b);
    cout << ans;


    return 0;
}