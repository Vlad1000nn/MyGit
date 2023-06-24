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

    cin.tie(0);                               //�  С›� ЎвЂљ�  С”�  В»� Ў� ‹� ЎвЂЎ�  В°�  Вµ� ЎвЂљ � Ў� ѓ�  � � � Ў� Џ�  В·�  С”� ЎС“ cin �  С” cout
    std::ios_base::sync_with_stdio(false);    //�  С›� ЎвЂљ�  С”�  В»� Ў� ‹� ЎвЂЎ�  В°�  Вµ� ЎвЂљ � Ў� ѓ�  С‘�  � …� ЎвЂ¦� Ў� ‚�  С•�  � …�  С‘�  В·�  В°� ЎвЂ �  С‘� Ў� ‹ cout/cin �  С‘ print/scanf

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