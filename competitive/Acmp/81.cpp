#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int N;
    int mina = 1000000;
    int maxa = -1;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        if (x > maxa)
            maxa = x;
        if (x < mina)
            mina = x;
    }
    cout << mina << ' ' << maxa;
    fclose(stdin);
    fclose(stdout);
    return 0;
}