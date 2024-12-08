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


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    std::vector<std::string> field;
    while (std::getline(fin, line))
        field.push_back(line);

    const int n = isz(field);
    const int m = isz(field[0]);

    std::map<int, std::vector<std::pair<int, int>>> pos;
    vector<pair<int, int>> answ;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (field[i][j] == '.')
                continue;
            pos[field[i][j]].push_back(std::make_pair(i, j));
        }
    
    for (auto& [key, val] : pos)
    {
        // val вектор символов
        const int cnt = isz(val);
        for (int i = 0; i < cnt; ++i)
        {
            for (int j = i + 1; j < cnt; ++j)
            {
                int dx = val[j].first - val[i].first;
                int dy = val[j].second - val[i].second;
                int nextDx1 = val[i].first - dx;
                int nextDy1 = val[i].second - dy;
                int nextDx2 = val[j].first + dx;
                int nextDy2 = val[j].second + dy;

                while (nextDx1 >= 0 && nextDy1 >= 0 && nextDx1 < n && nextDy1 < m) {
                    if(field[nextDx1][nextDy1] == '.')
                        answ.emplace_back(nextDx1, nextDy1);
                    nextDx1 -= dx;
                    nextDy1 -= dy;
                }
                while (nextDx2 >= 0 && nextDy2 >= 0 && nextDx2 < n && nextDy2 < m) {
                    if(field[nextDx2][nextDy2] == '.')
                        answ.emplace_back(nextDx2, nextDy2);
                    nextDx2 += dx;
                    nextDy2 += dy;
                }
            }
        }
    }

    std::set<pair<int, int>> s(all(answ));
    int answer = isz(s);
    for (auto& it : pos)
        answer += isz(it.second);

    cout << answer << '\n'; 

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
