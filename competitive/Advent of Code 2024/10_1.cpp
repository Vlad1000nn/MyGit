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


    std::queue<std::tuple<int, int, int>> q;
    int cnt{};
    for (int i = 1; i< n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (field[i][j] == '0')
            {
                q.push({ i,j,cnt + 1  });
                ++cnt;
            }
        }
    }
    const int k = isz(q);

    vvvi visit(k + 1, vvi(n + 1, vi(m + 1)));

    vi answ(k + 1);

    while (!q.empty())
    {
        auto [row, col, num] = q.front();
        q.pop();

        if (field[row][col] == '.' || visit[num][row][col])
            continue;
        visit[num][row][col] = 1;
        if (field[row][col] == '9')
            answ[num]++;

        for (int i = 0; i < 4; ++i)
        {
            int nextRow = row + N[i][0], nextCol = col + N[i][1];
            if (field[nextRow][nextCol] - field[row][col] == 1)
                q.push({ nextRow, nextCol, num });
        }
    }

    ll sum = std::accumulate(all(answ), 0ll);
    std::cout << sum << '\n';
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
