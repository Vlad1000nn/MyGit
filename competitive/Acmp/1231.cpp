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
    int k = { 0 };
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int g = i + 1; g < n; g++)
        {
            if (N[g] < N[i])
                k++;
        }
    }
    cout << k;

    return 0;
}