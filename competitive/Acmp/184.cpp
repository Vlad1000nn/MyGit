#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <cstdio>

using namespace std;

const int Month[13]{ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
constexpr int day_hours = { 8 };

int sum_dif_month(int n2, int n1)
{
    int sum = { 0 };
    for (int i = n1 + 1; i < n2; i++)
    {
        sum += Month[i];
    }
    return sum;
}

int main()
{

    int n;
    cin >> n;
    vector<pair<string, tuple<int, int, int, int>>> vec;

    string s_errrrrrr;
    getline(cin, s_errrrrrr);   //избегаем записи пустой строки

    for (int i = 0; i < n; i++)
    {
        string str;
        getline(cin, str);      //вводим строку

        int day, month, hours, minutes;     //Присваиваем значенмя
        sscanf_s(str.c_str(), "%02d.%02d. %02d:%02d", &day, &month, &hours, &minutes);

        char result[100];   //Меняем местами дни и месяцы чтобы отсортировать
        sprintf_s(result, "%02d.%02d. %02d:%02d", &month, &day, &hours, &minutes);
        str = result;

        //Пихаем в вектор
        vec.push_back(make_pair(str, make_tuple(month, day, hours, minutes)));
    }

    //Сортируем
    sort(vec.begin(), vec.end());

    /*cout << '\n';
    for (int i = 0; i < n; i++)
    {
        cout << get<0>(vec[i].second) << ' ' << get<1>(vec[i].second) << ' ' << get<2>(vec[i].second) << ' ' << get<3>(vec[i].second) << '\n';
    }
    cout << '\n';*/

    int sum_hours{ 0 }, sum_minutes{ 0 };

    //Берём i=0 и идём по парам(i и i+1) с шагом i+=2 
    for (int i = 0; i < n; i += 2)
    {
        //Количество часов до конца рабочего дня
        sum_hours += (18 - get<2>(vec[i].second));
        //количество минут до конца часа
        sum_minutes += (60 - get<3>(vec[i].second));
        //Количество часов после начала дня
        sum_hours += get<2>(vec[i + 1].second) - 10;
        //Количество минут после начала дня
        sum_minutes += get<3>(vec[i + 1].second);

        //добавляем полные рабочие дни(разность*8часовой)

        //Если один месяц то просто разность
        if (get<0>(vec[i].second) == get<0>(vec[i + 1].second))
            sum_hours += day_hours * (get<1>(vec[i + 1].second) - get<1>(vec[i].second) - 1);
        else
            //если разные месяцы то сумма за второй месяц+ количество дней до конца первого месяца
            sum_hours += day_hours * (get<1>(vec[i + 1].second) + sum_dif_month(get<0>(vec[i + 1].second), get<0>(vec[i].second)) + Month[get<0>(vec[i].second)] - get<1>(vec[i].second) - 1);

        //отнимаю час из-за добавления 60 минут
        sum_hours -= 1;
        //+минута за каждую завершённую пару
        sum_minutes += 1;
        /*    printf("%02d:%02d", sum_hours, sum_minutes);
            cout << '\n';*/
    }

    sum_hours += sum_minutes / 60;
    sum_minutes %= 60;


    printf("%d:%02d", sum_hours, sum_minutes);


    return 0;
}