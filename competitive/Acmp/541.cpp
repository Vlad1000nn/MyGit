#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;


string s1_maximum, s2_minimum;


//сведение двух строк к равному количеству разрядов
void normalization(string& s1, string& s2)
{
    while (s1.size() < s2.size())
        s1 = '0' + s1;
    while (s2.size() < s1.size())
        s2 = '0' + s2;
}



string get_string(int k, string& s)
{
    string ANS = s;
    for (int i = 0; i <= k; i++)
        ANS += s[i];
    ANS = ANS.substr(k + 1);
    return ANS;
}

// Просто сравнение строк
int cmp(string& x, string& y)
{
    if (x.size() != y.size())
        return (x.size() < y.size()) ? -1 : 1;

    for (int i = 0; i < x.size(); i++)
    {
        if ((x[i] - '0') != y[i] - '0')
            return (x[i] - '0') < (y[i] - '0') ? -1 : 1;
    }
    return 0;

}




//Считаю все циклические сдвиги(без учёта тех,что начинаются с 0) и записываю в вектор
void solve(string& s1, string& s2)
{
    string buff = s1;
    string buff2 = s2;

    s1_maximum = s1;
    for (int i = 0; i < s1_maximum.size(); i++) s1_maximum[i] = '0';
    s2_minimum = s2;
    for (int i = 0; i < s2_minimum.size(); i++) s2_minimum[i] = '9';

    for (int i = 0; i < s1.size(); i++)
    {
        rotate(buff.begin(), buff.begin() + 1, buff.end());
        if (buff[0] != '0' && cmp(s1_maximum, buff) == -1)
        {
            //cout << s1_maximum << " changed to " << buff << '\n';
            s1_maximum = buff;
        }
    }


    for (int i = 0; i < s2.size(); i++)
    {
        rotate(buff2.begin(), buff2.begin() + 1, buff2.end());
        if (buff2[0] != '0' && cmp(s2_minimum, buff2) == 1)
        {
            //cout << s2_minimum << " changed to " << buff2 << '\n';
            s2_minimum = buff2;
        }
    }
}

//Ниже лежат функции для решения задачи на разность(для вывода ответа)



//Вывод с учётом знака,начиная с first_pos(первый ненулевой символ)
void print(string& N, bool sign, int first_pos)
{
    if (sign) cout << '-';
    for (int i = first_pos; i < N.size(); i++)
        cout << N[i];
    cout << '\n';
}

//� азность чисел
void calculate(string& s1, string& s2, string& ANS)
{
    normalization(s1, s2);
    normalization(ANS, s1);

    for (int i = s1.size() - 1; i >= 0; i--)
    {
        int x = s1[i] - s2[i];
        if (x < 0)
        {
            x += 10;
            s1[i - 1] -= 1;
        }
        ANS[i] = x + '0';
    }
}
//Конец решения


int main()
{
    string s1, s2, ans;
    cin >> s1 >> s2;
    if (cmp(s1, s2) == 0)
    {
        cout << '0';
        return 0;
    }

    solve(s1, s2);

    //Здесь решение пред задачи(разность чисел), для вывода ответа
    bool sign = { false };
    int first_pos{ 0 };

    switch (cmp(s1_maximum, s2_minimum))
    {
    case -1:
    {
        calculate(s2_minimum, s1_maximum, ans);
        sign = true;
        while (ans[first_pos] == '0')first_pos++;
        print(ans, sign, first_pos);
        break;
    }
    case 0: cout << '0'; break;
    case 1:
    {
        calculate(s1_maximum, s2_minimum, ans);
        while (ans[first_pos] == '0')first_pos++;
        print(ans, sign, first_pos);
        break;
    }
    default: cout << "??";
    }


    return 0;
}