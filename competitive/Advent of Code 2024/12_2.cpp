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

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for (auto& it : vec)
        out << it << ' ';

    return out;
}

// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


class DSU
{
private:

    vi parent, sz;
    int cnt;
public:

    int getParent(int x)
    {
        return x == parent[x] ? x : parent[x] = getParent(parent[x]);
    }

public:

    DSU(const int n)
        : sz(n + 1, 1)
        , parent(n + 1)
        , cnt(n)
    {
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }

    void merge(int x, int y)
    {
        x = getParent(x);
        y = getParent(y);

        if (x == y)
            return;

        sz[x] += sz[y];
        parent[y] = x;
        cnt--;
    }
};

void dfs(const std::vector<std::string>& field, int i, int j, std::vector<std::vector<int>>& visit, ll& currS, ll& currP, 
    const int id, vector<set<tuple<int,int,int>>>& sides)
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
        for (int dir = 0; dir < 4; ++dir) {
            for (int k = 0; k < 4; ++k)
            {
                int nextRow = row + N[k][0];
                int nextCol = col + N[k][1];
                if (field[nextRow][nextCol] == field[row][col]) 
                    q.push({ nextRow, nextCol });
                else 
                    sides[id].insert({ row, col,k });
            }
        }
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

    // Сначала сделаем вектор на 4 * n * m 
    // Теперь делаем DSUшку
    // При обходе смотрим по сторонам и ищем такие же
    // Если есть объединяем в ДСУ
    DSU dsu(4 * (n - 1) * (m - 2));

    auto getIndex = [&](int i, int j, int dir)
        {
            return dir + 4 * ((j - 1) * (n-1) + (i - 1));
        }; 
    vector<set<tuple<int, int, int>>> sides;
    int id = 0;

    vi s, p;
    ll answ{}, currS, currP;
    vvi visit(n + 1, vi(m, 0));
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m - 1; ++j)
        {
            currS = currP = 0;
            if (!visit[i][j]) {
                sides.push_back({});
                dfs(field, i, j, visit, currS, currP, id, sides);


                for (auto& [row,col,dir] : sides.back())
                {
                    for (auto newDir : { (dir + 1) % 4, (dir + 3) % 4 })
                    {
                        const int nrow = row + N[newDir][0];
                        const int ncol = col + N[newDir][1];
                        if (sides.back().count(make_tuple(nrow, ncol, dir)))
                            dsu.merge(getIndex(row, col, dir), getIndex(nrow, ncol, dir));
                    }
                }

                set<int> uniqSides;
                for (auto& [row, col, dir] : sides.back())
                    uniqSides.insert(dsu.getParent(getIndex(row, col, dir)));

                currP = isz(uniqSides);
                answ += currS * currP;
                ++id;
            }
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
