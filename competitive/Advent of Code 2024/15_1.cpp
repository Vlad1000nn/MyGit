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


void move(vector<string>& field, int step, int& row, int& col)
{
    const int nextRow = row + N[step][0];
    const int nextCol = col + N[step][1];
    int currRow = nextRow, currCol = nextCol;

    while (field[currRow][currCol] == 'O')
    {
        currRow += N[step][0];
        currCol += N[step][1];
    }
    if (field[currRow][currCol] == '#')
        return;
    field[currRow][currCol] = 'O';
    field[row][col] = '.';
    field[nextRow][nextCol] = '@';
    row = nextRow;
    col = nextCol;
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;
   
    std::vector<std::string> field;

    while (getline(fin, line)) {
        field.push_back(line);
    if(!isz(line))
        break;
    }

    const int n = isz(field);
    const int m = isz(field[0]);

    std::vector<int> steps;

    while (getline(fin, line))
        for (auto& it : line)
            if (it == '^')
                steps.push_back(0);
            else if (it == '>')
                steps.push_back(1);
            else if (it == 'v')
                steps.push_back(2);
            else if (it == '<')
                steps.push_back(3);

    int posx, posy;
    for(int i = 0;i<n;++i)
        for(int j = 0;j<m;++j)
            if (field[i][j] == '@')
            {
                posx = i;
                posy = j;
            }

    for (auto& it : steps)
        move(field, it, posx, posy);

    ll answ{};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (field[i][j] == 'O')
                answ += 100 * i + j;
    std::cout << answ << '\n';


    for (auto& it : field)
        cout << it << '\n';
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
