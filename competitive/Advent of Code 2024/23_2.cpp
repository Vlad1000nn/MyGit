#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;


int get_bit(const ll& x, ll index)
{
    return (x >> index) & 1;
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    // Задан граф, нужно найти самую большую по размеру клику (и её представителей)

    char str1[3]; 
    char str2[3]; 

    std::map<std::string, std::set<std::string>> graph;

    while (getline(fin, line))
    {
        sscanf_s(line.c_str(), "%2s-%2s", &str1, 3, &str2, 3);

        graph[str1].insert(str2);
        graph[str2].insert(str1);
    }
    const int n = isz(graph);
    std::vector<std::string> answ;
    std::vector<std::string> curr;

    // Поскольку количество соседей <= 13, просто для каждой вершины переберём все подмножества соседей и проверим их на связность
    for (auto& [key, val] : graph)
    {
        const int m = isz(val);
        std::vector<std::string> neighbours(all(val)); 

        for (int mask = 1; mask < (1 << m); ++mask)
        {
            curr.clear();
            curr.push_back(key);
            for (int i = 0; i < m; ++i)
                if (get_bit(mask, i))
                    curr.push_back(neighbours[i]);


            const int k = isz(curr);
            bool ok = true;
            for (int i = 0; i < k; ++i)
                for (int j = i + 1; j < k; ++j)
                    if (std::find(all(graph[curr[i]]), curr[j]) == graph[curr[i]].end()) {
                        ok = false;
                        goto next;
                    }

            next:
            if (ok && isz(answ) < isz(curr))
                answ = curr;
        }
    }
    
    sort(all(answ));
    for (auto& it : answ)
        cout << it << ",";
 
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
