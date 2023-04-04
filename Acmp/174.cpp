#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iomanip>

using namespace std;



int main()
{

    // freopen("INPUT.TXT", "r", stdin);
    // freopen("OUTPUT.TXT", "w", stdout);

     //cin.tie(0);                  //Ð  Ð¡â€ºÐ ÐŽÐ²Ð‚Ñ™Ð  Ð¡â€Ð  Ð’Â»Ð ÐŽÐ â€¹Ð ÐŽÐ²Ð‚ÐŽÐ  Ð’Â°Ð  Ð’ÂµÐ ÐŽÐ²Ð‚Ñ™ Ð ÐŽÐ Ñ“Ð  Ð â€ Ð ÐŽÐ ÐÐ  Ð’Â·Ð  Ð¡â€Ð ÐŽÐ¡â€œ cin Ð  Ð¡â€ cout
     //std::ios_base::sync_with_stdio(false);    //Ð  Ð¡â€ºÐ ÐŽÐ²Ð‚Ñ™Ð  Ð¡â€Ð  Ð’Â»Ð ÐŽÐ â€¹Ð ÐŽÐ²Ð‚ÐŽÐ  Ð’Â°Ð  Ð’ÂµÐ ÐŽÐ²Ð‚Ñ™ Ð ÐŽÐ Ñ“Ð  Ð¡â€˜Ð  Ð â€¦Ð ÐŽÐ²Ð‚Â¦Ð ÐŽÐ â€šÐ  Ð¡â€¢Ð  Ð â€¦Ð  Ð¡â€˜Ð  Ð’Â·Ð  Ð’Â°Ð ÐŽÐ²Ð‚ Ð  Ð¡â€˜Ð ÐŽÐ â€¹ cout/cin Ð  Ð¡â€˜ print/scanf

    int n;
    double a;
    int N[100];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }
    sort(N, N + n);
    cin >> a;
    for (int i = 0; i < n; i++)
    {
        if (a < N[i])
            a = (a + N[i]) / 2;
    }
    cout << fixed;
    cout.precision(6);
    cout << a;

    return 0;
}