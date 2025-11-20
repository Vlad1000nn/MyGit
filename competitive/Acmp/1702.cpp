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


    int N[1000];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }

    for (int g = n - 1; g >= 0; g--)
    {
        int nmax = N[0];
        int imax = 0;
        for (int i = 0; i <= g; i++)
        {
            if (N[i] > nmax)
            {
                nmax = N[i];
                imax = i;
            }
        }
        swap(N[imax], N[g]);
        cout << imax << ' ';
    }

    return 0;
}