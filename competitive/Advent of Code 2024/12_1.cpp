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

const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};


void dfs(const std::vector<std::string>& field, int i, int j, std::vector<std::vector<int>>& visit, ll& currS, ll& currP)
{
    std::queue<std::tuple<int, int>> q;
    q.push({ i,j });
    while (!q.empty())
    {
        auto [row, col] = q.front();
        q.pop();

        if (visit[row][col] || field[row][col] == '#')
            continue;
        visit[row][col] = 1;
        currS += 1;

        int neighbours = 0;
        for (int k = 0; k < 4; ++k)
        {
            int nextRow = row + N[k][0];
            int nextCol = col + N[k][1];
             if (field[nextRow][nextCol] == field[row][col]) {
                neighbours++;
                q.push({ nextRow, nextCol });
            }
        }
        currP += 4 - neighbours;
    }
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    std::vector<std::string> field;
    field.push_back("#");
    while (std::getline(fin, line))
        field.push_back('#' + line + '#');
    field.push_back("#");
    const int n = isz(field) - 1;
    const int m = isz(field[1]);
    field[0] = field[n] = std::string(m, '#');

    ll answ{}, currS, currP;
    vvi visit(n + 1, vi(m, 0));
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m - 1; ++j)
        {
            currS = currP = 0;
            if (!visit[i][j]) 
                dfs(field, i, j, visit, currS, currP);
          
            answ += currS * currP;
        }
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
 