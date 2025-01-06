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

// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    vector<string> field;
    while (getline(fin, line))
        field.push_back(line);
    
    int sx, sy, fx, fy;

    const int n = isz(field);
    const int m = isz(field[0]);

    for(int i = 0;i<n;++i)
        for (int j = 0; j < m; ++j)
        {
            if (field[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
            if (field[i][j] == 'E')
            {
                fx = i;
                fy = j;
            }
        }

    vvi dist(n, vi(n, INF));

    queue<tuple<int, int, int>> q;
    q.push(make_tuple(0, sx, sy));
    while (!q.empty())
    {
        auto [curr, row, col] = q.front();
        q.pop();

        if (field[row][col] == '#' || curr >= dist[row][col])
            continue;
        dist[row][col] = curr;

        for (int k = 0; k < 4; ++k)
            q.push(make_tuple(curr + 1, row + N[k][0], col + N[k][1]));
    }
    int answ{};
 
    // Просто перебираем точку входа и выхода
    for (int i = 1; i < n - 1; ++i)
        for (int j = 1; j < m - 1; ++j)
            if (field[i][j] != '#')
                for (int k = 1; k < n - 1; ++k)
                    for (int l = 1; l < m - 1; ++l)
                        if (field[k][l] != '#')
                        {
                            int cheat = abs(k - i) + abs(l - j);
                            if (cheat <= 20 && dist[k][l] - dist[i][j] - cheat >= 100)
                                ++answ;
                        }

    std::cout << answ << '\n';

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
