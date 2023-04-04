#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

int factorials(int x, int y)
{
    int k = 1;
    int sum = { x };
    while (k * y < x)
    {
        sum *= (x - k * y);
        k++;
    }
    return sum;
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    string s1, s2;
    cin >> s1 >> s2;
    int x = stoi(s1);
    int y = s2.size();
    cout << factorials(x, y);

    return 0;
}