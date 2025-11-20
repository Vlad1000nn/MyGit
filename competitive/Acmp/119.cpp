#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;



int main()
{

    // freopen("INPUT.TXT", "r", stdin);
    // freopen("OUTPUT.TXT", "w", stdout);

     //cin.tie(0);                  //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ІСЏ� ·� єСѓ cin � є cout
     //std::ios_base::sync_with_stdio(false);    //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ё� ЅС…СЂ� ѕ� Ѕ� ё� ·� °С� � ёСЋ cout/cin � ё print/scanf

    int h, n, m, s;
    int N[101];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> h >> m >> s;
        N[i] = 3600 * h + 60 * m + s;
    }

    sort(N, N + n);

    for (int i = 0; i < n; i++)
    {
        m = N[i] / 60;      //7300 121*60 +40
        s = N[i] % 60;
        h = m / 60;
        m %= 60;
        cout << h << ' ' << m << ' ' << s << '\n';
    }

    return 0;
}