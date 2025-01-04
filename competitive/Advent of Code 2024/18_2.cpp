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

using vpii = vector<pair<int,int>>;

// РџРµСЂРµР±РѕСЂ РЅР°РїСЂР°РІР»РµРЅРёР№
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);


bool check(const vvi& field)
{
    const int n = isz(field) - 2;
    vvi visit(n + 2, vi(n + 2, INF));

    PriorityQueue<tuple<int, int, int>> pq;
    pq.push(make_tuple(0, 1, 1));
    while (!pq.empty())
    {
        auto [dist, row, col] = pq.top();
        pq.pop();

        if (dist >= field[row][col] || dist >= visit[row][col])
            continue;

        visit[row][col] = dist;
        for (int k = 0; k < 4; ++k)
            pq.push(make_tuple(dist + 1, row + N[k][0], col + N[k][1]));
    }

    return visit[n][n] != INF;
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    const int n = 71;
    // Поле будем хранить как номер секунды, с которой клетка стала решёткой 

    vvi field(n + 2, vi(n + 2, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            field[i][j] = INF;

    vpii input;
    while (getline(fin, line))
    {
        int x, y;
        sscanf_s(line.c_str(), "%d,%d", &x, &y);

        input.emplace_back(y + 1, x + 1);
    }

    const int m = isz(input);

    // Мне лень переписывать быстрое решение, просто проверим на каждом шаге можем дойти или нет
    int ansx, ansy;
    for (int i = 0; i < m; ++i)
    {
        field[input[i].first][input[i].second] = 0;
        if (!check(field))
        {
            for (auto& it : field)
            {
                for (auto& it2 : it)
                    cout << (it2 == INF ? '.' : '#');
                cout << '\n';
            }
            ansx = input[i].second - 1;
            ansy = input[i].first -1;
            break;
        }
    }

    cout << ansx << ',' << ansy << '\n';
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
