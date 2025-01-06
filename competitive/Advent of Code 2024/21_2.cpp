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

const int INF = int(1e9);
const ll INFL = ll(1e18);

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


/*
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+
*/
// На эту штуку нажимает робот с такой раслкадкой:

/*
   +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/
// Теперь у нас цикл из 25 таких панелей

const char direction[] = { '^', '>', 'v', '<' };

void calculate_dist(const vector<string>& panel, map<pair<char,char>, set<string>>& dist)
{
    const int n = isz(panel);
    const int m = isz(panel[0]);
    queue<tuple<char,char, string, int, int, int>> q; // (откуда начали, предыдущий символ(чтобы туда сюда не ходить), текущая строка-путь,
                                                       // строка, столбец, флаг (если 0 то можем ходить только ^>, 1 >v, 2 v<, 3 <^ 
    for(int i = 0;i<n;++i)
        for (int j = 0; j < m; ++j)
        {
            if (panel[i][j] == '#')
                continue;
            q.push(make_tuple(panel[i][j], 0,"", i, j, 0));
            q.push(make_tuple(panel[i][j], 0,"", i, j, 1));
            q.push(make_tuple(panel[i][j], 0,"", i, j, 2));
            q.push(make_tuple(panel[i][j], 0,"", i, j, 3));
        }
    while (!q.empty())
    {
        auto [from,prev, route, row, col, flag] = q.front();
        q.pop();

        if (row < 0 || col < 0 || row >= n || col >= m || panel[row][col] == '#')
            continue;

        dist[make_pair(from, panel[row][col])].insert(route);


        for (int k : { flag, (flag + 1) % 4})  {
            const int nextRow = row + N[k][0];
            const int nextCol = col + N[k][1];
            if (nextRow >= 0 && nextCol >= 0 && nextRow < n && nextCol < m && panel[nextRow][nextCol] != prev)
                q.push(make_tuple(from, panel[row][col], route + direction[k], nextRow, nextCol, flag));
        }
    }
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    const int n = 25; // Количество роботов

    std::vector<std::string> codes;
    while (getline(fin, line))
        codes.push_back('A' + line);

    std::string indexes = "^>v<A";
    auto getIndex = [&](const char& x) {
        return indexes.find(x);
        };

    const vector<string> robot_panel = { "#^A", "<v>" };
    const vector<string> keypad_panel = { "789", "456", "123", "#0A" };
    map<pair<char, char>, set<string>> robot_dist, keypad_dist;
    
    // Генерируем все комбинации всех пар символов в таблицах
    calculate_dist(robot_panel, robot_dist);
    calculate_dist(keypad_panel, keypad_dist);

    //--------------------------------------------------PART 2--------------------------------------------//

    ll answer{};

    // Пишем динамику dp[i][from][to] -> Сколько нужно шагов, чтобы подвинуть i-го робота из from в to

    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(5, vector<ll>(5, INFL)));
    
    for (auto& [key, val] : robot_dist)
    {
        char x = key.first;
        char y = key.second;
        int curr{ INF };
        for (auto& it : val)
            setmin(curr, isz(it));
        dp[n-1][getIndex(x)][getIndex(y)] = curr;
    }

    for (int i = n-2; i >= 0; --i)
    {
        for (char j : indexes)
        {
            for (char k : indexes)
            {
                for (auto& it : robot_dist[make_pair(j, k)])
                {
                    ll sum{};
                    std::string need = 'A' + it;
                    for (int l = 1; l < isz(need); ++l)
                    {
                        sum += dp[i + 1][getIndex(need[l - 1])][getIndex(need[l])] + 1;
                    }
                    if (isz(need) == 0)
                        sum  = 0;
                    else
                        sum += dp[i + 1][getIndex(need.back())][getIndex('A')];

                    setmin(dp[i][getIndex(j)][getIndex(k)], sum);
                }
            }
        }
    }

    // Теперь просто переводим наш путь в шаги первого робота и складываем динамику
    ll final_answ{};
    ll answ{};
    for (auto& it : codes)
    {
        answ = INFL;
        std::string need = 'A' + it;
        std::set<std::string> routes;
        queue<pair<string, int>> q;
        q.push(make_pair("", 1));
        while (!q.empty())
        {
            auto [curr, index] = q.front();
            q.pop();

            if (index == isz(need))
            {
                routes.insert(curr);
                continue;
            }
            for (auto& it : keypad_dist[make_pair(need[index - 1], need[index])])
                q.push(make_pair(curr + it + 'A', index + 1));
        }

        for (auto& gg : routes)
        {
            ll curr = 0;
            for (int i = 1; i < isz(gg); ++i)
                curr += dp[0][getIndex(gg[i - 1])][getIndex(gg[i])] + 1;
            // Обновляем ответ
            setmin(answ, curr);
        }
        final_answ += 1ll * stoi(it.substr(1, isz(it) - 1)) * answ;

    }

    std::cout << final_answ << '\n';

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
