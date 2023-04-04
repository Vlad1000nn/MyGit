#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;


int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int a, b, c;
    cin >> a >> b >> c;
    if (a * b == c)
        cout << "YES";
    else
        cout << "NO";

    fclose(stdin);
    fclose(stdout);

    return 0;
}