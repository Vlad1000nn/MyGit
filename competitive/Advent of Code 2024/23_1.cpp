#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;

using vi = vector<int>;
using vvi = vector<vi>;


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    // Задан граф, нужно найти тройки связных вершин, хотя бы 1 из которых начинается с буквы t

    std::map<std::string, std::vector<std::string>> graph;
    char str1[3]; 
    char str2[3]; 

    while (getline(fin, line))
    {
        sscanf_s(line.c_str(), "%2s-%2s", &str1, 3, &str2, 3);
        graph[str1].push_back(str2);
        graph[str2].push_back(str1);
    }

    // Поскольку нам нужны тройки вершин, просто будем перебирать пары соседей у всех tшек
    // Если среди них есть связь, то добавляем к ответу(если один из них тоже tшка, то учитываем это)
    int answ{};
    int not_good{};
    for (auto& [key, val] : graph)
    {
        if (key[0] != 't')
            continue;
        const int k = isz(val);
        for(int i = 0;i<k;++i)
            for (int j = i + 1; j < k; ++j)
                if (std::find(all(graph[val[i]]), val[j]) != graph[val[i]].end())
                {
                    if (val[i][0] == 't' || val[j][0] == 't')
                        ++not_good;
                    ++answ;
                }
            
    }
    cout << answ - not_good / 2 << '\n';
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--)
        solve();

    return 0;
}
