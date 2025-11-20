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
    cout << max(max(a, c), b) - min(min(a, c), b);

    fclose(stdin);
    fclose(stdout);

    return 0;
}