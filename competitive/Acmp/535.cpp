#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <array>
#include <set>


using namespace std;

//Сравнение строк
bool cmp(string x, string y)
{
    if (x.size() != y.size())
        return (x.size() > y.size()) ? false : true;

    for (int i = 0; i < x.size(); i++)
    {
        if ((x[i] - '0') != y[i] - '0')
            return (x[i] - '0') > (y[i] - '0') ? false : true;
    }
    return false;

}

void normalization(string& s1, string& s2)
{
    while (s1.size() < s2.size())
        s1 = '0' + s1;
    while (s2.size() < s1.size())
        s2 = '0' + s2;
}


string calculate(long long a, long long b)
{
    string s1 = to_string(a);
    string s2 = to_string(b);
    string ans;

    normalization(s1, s2);  //Добавляем 0 если разные длины строк

    for (int i = s1.size() - 1; i >= 0; i--)
    {
        string sum = to_string((s1[i] - '0') + (s2[i] - '0'));
        reverse(sum.begin(), sum.end());
        ans += sum;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    long long a, b, c;
    cin >> a >> b >> c;

    string s1, s2, s3;
    s1 = calculate(stoll(calculate(a, b)), c);          // (а+в)+с
    s2 = calculate(stoll(calculate(a, c)), b);          // (а+с)+в
    s3 = calculate(stoll(calculate(b, c)), a);          // а+(в+с)

    std::set<string> sums;

    sums.insert(s1);
    sums.insert(s2);
    sums.insert(s3);


    if (sums.size() > 1)
    {
        cout << "YES\n";
        //Хз как сортить set перезаписал в вектор :(
        vector<string> vec;
        for (set<string>::iterator it = sums.begin(); it != sums.end(); ++it)
            vec.push_back(*it);
        sort(vec.begin(), vec.end(), cmp);


        for (int i = 0; i < vec.size(); i++)
            cout << vec[i] << '\n';
    }
    else
        cout << "NO\n" << *sums.begin();


    return 0;
}