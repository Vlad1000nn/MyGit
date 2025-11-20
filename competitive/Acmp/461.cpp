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

    int n;
    int sum = { 0 };
    cin >> n;
    int N[10001];
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }
    sort(N, N + n);
    for (int i = 0; i < n / 2 + 1; i++)
    {
        sum += N[i] / 2 + 1;
    }
    cout << sum;

    return 0;
}