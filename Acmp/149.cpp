#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int N[1000];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        cout << N[i] << ' ';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}