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

////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    std::vector<std::string> field;
    field.push_back("#");
    while (std::getline(fin, line))
        field.push_back('.' + line + '.');
    field.push_back("#");

    const int n = isz(field) - 1;
    const int m = isz(field[1]) - 1;
    field[0] = field[n] = std::string(m, '.');

    std::vector<std::pair<int, int>> nine_poses;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            if (field[i][j] == '9')
                nine_poses.emplace_back(i, j);

    std::queue<std::tuple< int, int>> q;
    std::vector<std::vector<int>> visit(n + 1, std::vector<int>(m + 1));

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (field[i][j] == '0')
            {
                q.push({ i ,j });
                while (!q.empty()) {
                    auto [row, col] = q.front();
                    q.pop();
          
                    visit[row][col]++;

                    for (int k = 0; k < 4; ++k)
                    {
                        int nextRow = row + N[k][0], nextCol =col +  N[k][1];
                        if (field[nextRow][nextCol] - field[row][col] == 1)
                            q.push({ nextRow, nextCol });
                    }
                }
            }
        }
    }

    ll answ{};
    for (auto& [x, y] : nine_poses)
        answ += visit[x][y];
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
