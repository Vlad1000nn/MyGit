#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int x, y, a, b;
    cin >> a >> b;
    y = (a + sqrt(a * a - 4 * b)) / 2;
    x = a - y;
    cout << min(x, y) << ' ' << max(x, y);


    fclose(stdin);
    fclose(stdout);
    return 0;
}