#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    string str;
    int max = 0;
    int pos = { 0 };
    cin >> str;
    str.push_back('2');
    while (pos != string::npos)
    {
        pos = str.find('1');
        str = str.substr(pos + 1);
        if (pos > max)
            max = pos;
    }
    if (str.find('2') > max)
        max = str.find('2');
    cout << max;
    fclose(stdin);
    fclose(stdout);
    return 0;
}