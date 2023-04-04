#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int n, k1, k2;
    k1 = k2 = 0;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == 1)
            k1++;
        else
            k2++;
    }
    cout << min(k1, k2);


    fclose(stdin);
    fclose(stdout);
    return 0;
}