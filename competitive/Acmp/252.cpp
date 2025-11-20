#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>

using namespace std;


int main()
{
    int n;
    cin >> n;
    vector<tuple<long double, int, string>> vec;

    string s1;
    getline(cin, s1);   //Избегаем записи пустой строки в вектор


    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);

        int space = s.find(' ');

        string s_ans = s.substr(0, space);

        long double ans = stoi(s.substr(0, space));

        //Дальше проверки на единицы измерения
        if (space != s.size() - 2)
        {
            switch (s[space + 1])
            {
            case 'm':
            {
                ans /= 1e3;
                break;
            }
            case 'k':
            {
                ans *= 1e3;
                break;
            }
            case 'M':
            {
                ans *= 1e6;
                break;
            }
            case 'G':
            {
                ans *= 1e9;
                break;
            }
            default:
            {
                cout << "SMTH Wrong\n";
                break;
            }
            }
            space++;
        }
        switch (s[space + 1])
        {
        case 'g':
        {
            ans /= 1e6;
            break;
        }
        case 'p':
        {
            ans = (ans * 16380) / 1000000;
            break;
        }
        case 't':
        {
            break;
        }
        default:
        {
            cout << "Something Wrong\n";
            break;
        }
        }

        //Пуш бэкаем
        vec.push_back({ ans, i, s });
    }


    //Просто проверил свой вектор
   /* cout << '\n';
    for (int i = 0; i < vec.size(); i++)
    {
        cout << get<2>(vec[i]) << ' ' << get<1>(vec[i]) << '\n';
    }
    cout << '\n';

    */
    stable_sort(vec.begin(), vec.end());




    //Ответ
    for (int i = 0; i < vec.size(); i++)
    {
        cout << get<2>(vec[i]) << '\n';
    }

    return 0;
}