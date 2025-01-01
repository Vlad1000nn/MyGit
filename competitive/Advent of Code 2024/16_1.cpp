#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

template<typename T>
using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;

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
   
    std::vector<std::string> field;

    while (getline(fin, line))
        field.push_back(line);
    const int n = isz(field);
    const int m = isz(field[0]);

    int sx, sy, fx, fy;
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

    PriorityQueue<tuple<int, int, int, int>> pq;
    vvvi visit(n, vvi(m, vi(4, INF)));
    
    pq.push(make_tuple(0, 1, sx, sy));
    while (!pq.empty())
    {
        auto [dist, dir, row, col] = pq.top();
        pq.pop();

        if (visit[row][col][dir] <= dist)
            continue;

        if (field[row][col] == '#')
            continue;

        visit[row][col][dir] = dist;
        pq.push(make_tuple(dist + 1, dir, row + N[dir][0], col + N[dir][1]));
        pq.push(make_tuple(dist + 1000, (dir + 1) % 4, row, col));
        pq.push(make_tuple(dist + 1000, (dir + 3) % 4, row, col));
    }

    int answ = min({ visit[fx][fy][0],visit[fx][fy][1],visit[fx][fy][2],visit[fx][fy][3] });
    cout << answ << '\n';

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
