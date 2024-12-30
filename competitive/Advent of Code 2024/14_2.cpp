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



void setmax(auto& l, const auto& r)
{
    if (r > l)
        l = r;
}

void setmin(auto& l, const auto& r)
{
    if (r < l)
        l = r;
}



int bfs(const vector<string>& field, vvi& visit, int sx, int sy)
{
    const int n = isz(field);
    const int m = isz(field[0]);
    int group_size = 0;

    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));

    while (!q.empty())
    {
        auto [row, col] = q.front();
        q.pop();

        if (row < 0 || col < 0 || row >= n || col >= m || visit[row][col])
            continue;
        visit[row][col] = 1;
        group_size++;

        for (int k = 0; k < 4; ++k)
        {
            int nextRow = row + N[k][0];
            int nextCol = col + N[k][1];
            if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < m && field[nextRow][nextCol] == field[row][col] && ! visit[nextRow][nextCol])
                q.push(make_pair(nextRow, nextCol));
        }
    }

    return group_size;
}

bool check(vector<string>& field, vpii& p, const vpii& v)
{
    // сначала делаем шаг, потом чекаем уже
    const int n = isz(field);
    const int m = isz(field[0]);

    const int k = isz(p);
    for (int i = 0; i < k;++i)
    {
        int& px = p[i].first;
        int& py = p[i].second;

        field[px][py] = '.';
        int nextpx = (px + v[i].first + n) % n;
        int nextpy = (py + v[i].second + m) % m;
        field[nextpx][nextpy] = 'X';
        p[i] = make_pair(nextpx, nextpy);
    }
    

    // Ищем мегабольшую компоненту связности
    vvi visit(n, vi(m));

    int max_size = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (!visit[i][j] && field[i][j] != '.')
                setmax(max_size, bfs(field, visit, i, j));
        }

    return max_size >= 50;
}

void print(const vector<string>& field)
{
    for (auto& it : field)
        cout << it << '\n';
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;
    // поле 103 x 101
    const int n = 103;
    const int m = 101;

    vector<string> field(n, std::string(m, '.'));

    vpii p, v;

    while (getline(fin, line))
    {
        int px, py, vx, vy;
        sscanf_s(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        p.emplace_back(py, px);
        v.emplace_back(vy, vx);
        field[py][px] = 'X';
    }

    for (int i = 0; i < 101 * 103; ++i)
    {
        move(field, p, v);
        if (check(field,p, v)) {
            cout << '\n' << i + 1 << ":\n";
            print(field);
        }
    }

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
