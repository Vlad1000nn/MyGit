#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <array>
#include <set>


using namespace std;

int cmp(string x, string y)
{
    if (x.size() != y.size())
        return (x.size() < y.size()) ? -1 : 1;

    for (int i = 0; i < x.size(); i++)
    {
        if ((x[i] - '0') != y[i] - '0')
            return (x[i] - '0') < (y[i] - '0') ? -1 : 1;
    }
    return 0;

}

void normalization(string& s1, string& s2)
{
    while (s1.size() < s2.size())
        s1 = '0' + s1;
    while (s2.size() < s1.size())
        s2 = '0' + s2;
}

void print(string& N, bool sign, int first_pos)
{
    if (sign) cout << '-';
    for (int i = first_pos; i < N.size(); i++)
        cout << N[i];
    cout << '\n';
}


void calculate(string& s1, string& s2, string& ANS)
{
    normalization(s1, s2);
    normalization(ANS, s1);

    for (int i = s1.size() - 1; i >= 0; i--)
    {
        int x = s1[i] - s2[i];
        if (x < 0)
        {
            x += 10;
            s1[i - 1] -= 1;
        }
        ANS[i] = x + '0';

    }
}


int main()
{
    bool sign = { false };
    int first_pos{ 0 };

    string s1, s2, ans;
    cin >> s1 >> s2;

    switch (cmp(s1, s2))
    {
    case -1:
    {
        calculate(s2, s1, ans);
        sign = true;
        while (ans[first_pos] == '0')first_pos++;
        print(ans, sign, first_pos);
        break;
    }
    case 0: cout << '0'; break;
    case 1:
    {
        calculate(s1, s2, ans);
        while (ans[first_pos] == '0')first_pos++;
        print(ans, sign, first_pos);
        break;
    }
    default: cout << "??";
    }

    return 0;
}