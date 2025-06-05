#include <bits/stdc++.h>

#define isz(x) (int)x.size()

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;


// Шаги по сетке (0 вверх, 1 вправо, 2 вниз, 3 влево
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};


void setmin(auto& l, const auto& r)
{
    if (r < l)
        l = r;
}


std::string bfs(const vector<string>& field, int sx, int sy)
{
    const int n = isz(field); const int  m = isz(field[0]);
    std::string answ(100, 200);

    queue<tuple<string, int, int, int>> q;
    for (int dir = 1; dir < 3; ++dir) {
        if (field[sx + N[(dir + 2) % 4][0]][sy + N[(dir + 2) % 4][1]] != '#')
            continue;
        q.push(make_tuple("", sx, sy, dir));
    }

    vvvi visit(n, vvi(m, vi(4)));

    while (!q.empty())
    {
        auto [curr, row, col, dir] = q.front();
        q.pop();

        if (visit[row][col][dir] || !row || !col || row == n - 1 || col == m - 1 || field[row][col] == '#') {
            if (isz(curr) > 1)
                setmin(answ, curr);
            continue;
        }
        visit[row][col][dir] = 1;
        curr += field[row][col];

        q.push(make_tuple(curr, row + N[dir][0], col + N[dir][1], dir));
    }
    return answ;
}

/*
 Просто запускаемся с каждой клетки и собираем слова вниз и вправо(при условии, что нет букв сверху и снизу соответственно)
 Если собрали слово длины > 1 то добавили и обновили ответ
*/

void solve()
{
    int n, m; cin >> n >> m;
    vector<string> field(n+2); 
    string s;
    for (int i = 1; i <= n; ++i)
    {
        cin >> s;
        field[i] = '#' + s + '#';
    }
    field[0] = field[n + 1] = std::string(m + 2, '#');
    s = std::string(100, 200);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (field[i][j] != '#')
                setmin(s, bfs(field, i, j));
        }
    }
    
    cout << s << '\n';
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
