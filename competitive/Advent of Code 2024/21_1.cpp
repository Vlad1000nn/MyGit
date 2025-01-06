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

////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;

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
// А на этого робота нажимает робот 2 с такой же раскладкой

/*
   +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/

/*
   +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
*/

// А на этого робота нажимает робот 3 с такой же раскладкой
// А на этого робота нажимаем мы (то есть фактически мы двигаем курсор по 2 роботу)


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


// Первую часть я сдал полным перебором(пришлось подождать секунд 10 где-то)
void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    std::vector<std::string> codes;
    while (getline(fin, line))
        codes.push_back('A' + line);

    // ^>v<A
    const vector<string> robot_panel = { "#^A", "<v>" };
    const vector<string> keypad_panel = { "789", "456", "123", "#0A" };
    map<pair<char, char>, set<string>> robot_dist, keypad_dist;
    
    // Генерируем все комбинации всех пар символов в таблицах
    calculate_dist(robot_panel, robot_dist);
    calculate_dist(keypad_panel, keypad_dist);

    ll answer{};

    for (auto& keypad : codes)
    {
        std::string answ = std::string(INF, '#');
        const int n = isz(keypad);

        std::vector<std::string> need;  // Все возможные варианты передвижений по keypad
        std::vector<std::string> need2; // Все возможные варианты передвижений по robot
        
        queue<pair<std::string, int>> q;
        q.push(make_pair("", 1));
        while (!q.empty())
        {
            auto [curr, index] = q.front();
            q.pop();

            if (index == n) {
                need.push_back('A' + curr);
                continue;
            }

            for (auto& it : keypad_dist[make_pair(keypad[index - 1], keypad[index])])
                q.push(make_pair(curr + it + 'A', index + 1));
        }

        for (auto& gogogo : need)
        {
            q.push(make_pair("", 1));
            while (!q.empty())
            {
                auto [curr, index] = q.front();
                q.pop();
                if (index == isz(gogogo))
                {
                    need2.push_back('A' + curr);
                    continue;
                }
                for (auto& it : robot_dist[make_pair(gogogo[index - 1], gogogo[index])])
                    q.push(make_pair(curr + it + 'A', index + 1));
            }

        }

        for (auto& gogogo : need2)
        {
            q.push(make_pair("", 1));
            while (!q.empty())
            {
                auto [curr, index] = q.front();
                q.pop();
                if (index == isz(gogogo))
                {
                    if (isz(answ) > isz(curr))
                        answ = curr;
                    continue;
                }
                for (auto& it : robot_dist[make_pair(gogogo[index - 1], gogogo[index])])
                    q.push(make_pair(curr + it + 'A', index + 1));
            }

        }

        answer += 1ll * isz(answ) * stoi(keypad.substr(1, isz(keypad) - 2));
    }

    cout << answer << '\n';
   
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
