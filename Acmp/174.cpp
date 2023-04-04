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

     //cin.tie(0);                  //�  С›� ЎвЂљ�  С”�  В»� Ў� ‹� ЎвЂЎ�  В°�  Вµ� ЎвЂљ � Ў� ѓ�  � � � Ў� Џ�  В·�  С”� ЎС“ cin �  С” cout
     //std::ios_base::sync_with_stdio(false);    //�  С›� ЎвЂљ�  С”�  В»� Ў� ‹� ЎвЂЎ�  В°�  Вµ� ЎвЂљ � Ў� ѓ�  С‘�  � …� ЎвЂ¦� Ў� ‚�  С•�  � …�  С‘�  В·�  В°� ЎвЂ �  С‘� Ў� ‹ cout/cin �  С‘ print/scanf

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