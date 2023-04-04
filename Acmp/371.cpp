#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

int calculate(int k, int m)
{
    if (k == 1)
        return 0;
    int sum = { 1 };
    for (int i = sqrt(k); i > 1; i--)
    {
        if (k % i == 0)
        {
            sum += i;
            sum += k / i;
            if (sum > m)
                return 0;
        }
    }
    return sum;

}


int main()
{

    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    cin.tie(0);                  //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ІСЏ� ·� єСѓ cin � є cout
    std::ios_base::sync_with_stdio(false);    //� ћС‚� є� »СЋС‡� °� µС‚ СЃ� ё� ЅС…СЂ� ѕ� Ѕ� ё� ·� °С� � ёСЋ cout/cin � ё print/scanf

    vector<int> vec;
    string s = { "220,284,1184,1210,2620,2924,5020,5564,6232,6368,10744,10856,12285,14595,17296,18416,63020,76084,66928,66992,67095,71145,69615,87633,79750,88730,100485,124155,122265,139815,122368,123152,141664,153176,142310,168730,171856,176336,176272,180848,185368,203432,196724,202444,280540,365084,308620,389924,319550,430402,356408,399592,437456,455344,469028,486178,503056,514736,522405,525915,600392,669688,609928,686072,624184,691256,635624,712216,643336,652664,667964,783556,726104,796696,802725,863835,879712,901424,898216,980984," };

    while (s.size() > 1)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ',')
            {
                int x = stoi(s.substr(0, i));
                vec.push_back(x);
                s = s.substr(i + 1);
                i = 0;
            }
        }
    }
    /*  for (int i = 0; i < vec.size(); i ++ )
      {
          cout << vec[i] << '\n';
      }*/
      // cout << vec.size();

    int n, m;
    cin >> n >> m;
    bool flag = { false };
    for (int i = 0; i < vec.size(); i += 2)
    {
        if (vec[i] >= n && vec[i] <= m)
        {
            if (vec[i + 1] >= n && vec[i + 1] <= m)
            {
                flag = true;
                cout << vec[i] << ' ' << vec[i + 1] << '\n';
            }
        }
    }

    if (!flag)
        cout << "Absent";

    return 0;
}