#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <bitset>

using namespace std;



int main()
{
    //freopen("INPUT.TXT", "r", stdin);
    //freopen("OUTPUT.TXT", "w", stdout);

    cin.tie(0);                               //Ð  Ð¡â€ºÐ ÐŽÐ²Ð‚Ñ™Ð  Ð¡â€Ð  Ð’Â»Ð ÐŽÐ â€¹Ð ÐŽÐ²Ð‚ÐŽÐ  Ð’Â°Ð  Ð’ÂµÐ ÐŽÐ²Ð‚Ñ™ Ð ÐŽÐ Ñ“Ð  Ð â€ Ð ÐŽÐ ÐÐ  Ð’Â·Ð  Ð¡â€Ð ÐŽÐ¡â€œ cin Ð  Ð¡â€ cout
    std::ios_base::sync_with_stdio(false);    //Ð  Ð¡â€ºÐ ÐŽÐ²Ð‚Ñ™Ð  Ð¡â€Ð  Ð’Â»Ð ÐŽÐ â€¹Ð ÐŽÐ²Ð‚ÐŽÐ  Ð’Â°Ð  Ð’ÂµÐ ÐŽÐ²Ð‚Ñ™ Ð ÐŽÐ Ñ“Ð  Ð¡â€˜Ð  Ð â€¦Ð ÐŽÐ²Ð‚Â¦Ð ÐŽÐ â€šÐ  Ð¡â€¢Ð  Ð â€¦Ð  Ð¡â€˜Ð  Ð’Â·Ð  Ð’Â°Ð ÐŽÐ²Ð‚ Ð  Ð¡â€˜Ð ÐŽÐ â€¹ cout/cin Ð  Ð¡â€˜ print/scanf

    int  n, m{ 2 }, ans{ 1 };
    cin >> n;
    bitset<200000001> P;
    P.set();
    for (int i = 2; i <= n / 2; i++)
    {
        if (!P[i]) continue;
        for (int g = 2 * i; g <= n; g += i)
            P.reset(g);
    }

    if (n == 2) cout << "1";
    else
        cout << static_cast<int>(P.count()) - (200000002 - n);
    return 0;
}