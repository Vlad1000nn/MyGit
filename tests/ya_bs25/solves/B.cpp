#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vi = vector<int>;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

/*
    Пусть index - позиция искомого числа k. Банальное решение работает за O(n^2), перебираем l и r, и смотрим совпадает ли
    количество элементов >k и <k. 
    Давайте срежем n-ку.
    Предпосчитаем баланс для индексов (i = 0, i <= index) 
    Но баланс будем хранить не для каждого индекса, а суммарно будем иметь список балансов для чётных и нечётных индексов

    Теперь начинаем Перебирать правую границу (очевидно она начинается в index, заканчивается в n-1)
    Если мы отошли на нечётное количество позиций от index, то смотрим, есть ли у нас подходящий баланс на нечётных позициях
    в нашем предпосчёте слева, если есть то прибавляем к ответу количество таких балансов слева. То же самое с чётными

    // Итого имеем предпосчёт за n, перебор за n, n + n => O(n)
*/
void solve()
{
    int n, k; cin >> n >> k;
    vi a(n); cin >> a;
    int index = find(all(a), k) - a.begin();
    map<int, ll> left_odd, left_even;
    
    int curr{};
    ll answ{};
    for (int i = index,j = 0; i >= 0; --i,++j)
    {
        curr += (a[i] > k);
        curr -= (a[i] < k);
        if (j % 2 == 0)
            left_even[curr]++;
        else
            left_odd[curr]++;
    }
    curr = 0;
    for (int r = index, j = 0; r < n; ++r, ++j)
    {
        curr -= (a[r] > k);
        curr += (a[r] < k);
        if (j % 2 == 0)
            answ += left_even[curr];
        else
            answ += left_odd[curr];
    }

    cout << answ << '\n';
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1};

    while (t--) {
        solve();
    }

    return 0;
}
