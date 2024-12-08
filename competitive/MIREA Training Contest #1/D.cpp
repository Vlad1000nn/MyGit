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

const int INF = int(1e9);


using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


void solve()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m; fin >> n >> m;
    int k; fin >> k;
    vpii fire(k);
    for (auto& it : fire)
        fin >> it.first >> it.second;

    int cnt = n * m;
    PriorityQueue<std::tuple<int16_t, int16_t, int16_t>> pq;
    vvi visit(n + 2, vi(m + 2, INF));
    
    for (auto& it : fire) 
        pq.push({ 0, it.first, it.second });
    

    int lastx{ fire[0].first }, lasty{ fire[0].second };

    while (!pq.empty())
    {
        auto [dist, row, col] = pq.top();
        pq.pop();
       
        if (row == 0 || col == 0 || row == n + 1 || col == m + 1 || dist > visit[row][col])
            continue;
        lastx = row;
        lasty = col;

        visit[row][col] = dist;

        for (int i = 0; i < 4; ++i)
        {
            int nextRow = row + N[i][0];
            int nextCol = col + N[i][1];

            if (nextRow == 0 || nextRow == n + 1 || nextCol == 0 || nextCol == m + 1)
                continue;
            if (dist + 1 >= visit[nextRow][nextCol])
                continue;

            visit[nextRow][nextCol] = dist + 1;
            pq.push({ dist + 1, nextRow, nextCol });
            lastx = nextRow;
            lasty = nextCol;
        }

    }

    fout << lastx << ' ' << lasty << '\n';
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };
    //std::cin >> t;

	//stress();
    while (t--)
        solve();

    return 0;
}
