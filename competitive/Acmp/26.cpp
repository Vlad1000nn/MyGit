#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int x1, y1, x2, y2, r1, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double d = { sqrt(pow((x1 - x2),2) + pow(y1 - y2,2)) };

    if (d == 0)
    {
        cout << "NO";
        return 0;
    }
    if (d < max(r1, r2))
    {
        if (d + min(r1, r2) >= max(r1, r2))
        {
            cout << "YES";
            return 0;
        }
        else
        {
            cout << "NO";
            return 0;
        }
    }
    if (d <= r1 + r2)
        cout << "YES";
    else
        cout << "NO";



    fclose(stdin);
    fclose(stdout);
    return 0;
}