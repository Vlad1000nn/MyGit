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

    const int n = 71;
    // Поле будем хранить как номер секунды, с которой клетка стала решёткой 

    vvi field(n + 2, vi(n + 2, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            field[i][j] = INF;

    int sec = 0;
    while (getline(fin, line))
    {
        int x, y;
        sscanf_s(line.c_str(), "%d,%d", &x, &y);

        if(sec < 1024)
            field[y + 1][x + 1] = 0;
        // Уже особо не надо, авторам нужно было сразу 1024 выбросить и всё(
        sec++;
    }


    for (auto& it : field)
    {
        for (auto& it2 : it)
            cout << (it2 == INF ? '.' : '#');
        cout << '\n';
    }
    cout << "VISIT:\n";

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

    cout << visit[n][n] << '\n';
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
