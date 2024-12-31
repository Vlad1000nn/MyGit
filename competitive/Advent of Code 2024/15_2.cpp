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

bool check_move_box(const std::vector<std::vector<char>>& field, int step, int i, int j)
{
    const int n = isz(field);
    const int m = isz(field[0]);
    vvi visit(n, vi(m));
    queue<pair<int, int>> q;
    q.push(make_pair(i,j));
    if (field[i][j] == '[')
        q.push(make_pair(i, j + 1));
    if (field[i][j] == ']')
        q.push(make_pair(i, j - 1));
    while (!q.empty())
    {
        auto [row, col] = q.front();
        q.pop();

        int nextRow = row + N[step][0];
        int nextCol = col + N[step][1];
        if (field[row][col] == '.')
            continue;

        if (visit[row][col])
            continue;
        visit[row][col] = 1;

        if (field[nextRow][nextCol] == '#' || field[row][col] == '#')
            return false;
        
        if (field[row][col] == '[')
        {
            if (step == 0 || step == 2)
            {
                q.push(make_pair(nextRow, nextCol));
                q.push(make_pair(nextRow, nextCol + 1));
            }
            else if (step == 1){
                q.push(make_pair(row, nextCol + 1));
            }
            else if (step == 3) {
                q.push(make_pair(row, nextCol));
            }
        }
        else if (field[row][col] == ']')
        {
            if (step == 0 || step == 2) {
                q.push(make_pair(nextRow, nextCol));
                q.push(make_pair(nextRow, nextCol - 1));
            }
            else if (step == 1) {
                q.push(make_pair(row, nextCol));
            }
            else if (step == 3) {
                q.push(make_pair(row, nextCol - 1));
            }
        }
    }
    return true;
}

void move_box(std::vector<std::vector<char>>& field,vvi& visit,  int step, int row, int col)
{
    if (visit[row][col])
        return;
    visit[row][col] = 1;
    const int nextRow = row + N[step][0];
    const int nextCol = col + N[step][1];
    if (field[row][col] == '[')
    {
        visit[row][col + 1] = 1;
        if (step == 0 || step == 2)
        {
            if (field[nextRow][nextCol] == '[' || field[nextRow][nextCol] == ']')
                move_box(field, visit, step, nextRow, nextCol);
            if (field[nextRow][nextCol + 1] == '[' || field[nextRow][nextCol + 1] == ']')
                move_box(field, visit, step, nextRow, nextCol + 1);

            field[nextRow][nextCol] = '[';
            field[nextRow][nextCol+1] = ']';
            field[row][col] = '.';
            field[row][col + 1] = '.';
        }
        else if (step == 1) {
            if (field[nextRow][nextCol + 1] == '[')
                move_box(field, visit, step, nextRow, nextCol + 1);
            field[nextRow][nextCol] = '[';
            field[nextRow][nextCol + 1] = ']';
            field[row][col] = '.';
        }
        else if (step == 3) {
            if (field[nextRow][nextCol] == ']')
                move_box(field, visit, step, nextRow, nextCol);
            field[nextRow][nextCol] = '[';
            field[row][col] = ']';
            field[row][col + 1] = '.';
        }
    }
    else if (field[row][col] == ']'){
        visit[row][col - 1] = 1;
        if (step == 0 || step == 2)
        {
            if (field[nextRow][nextCol] == '[' || field[nextRow][nextCol] == ']')
                move_box(field, visit, step, nextRow, nextCol);
            if (field[nextRow][nextCol - 1] == '[' || field[nextRow][nextCol - 1] == ']')
                move_box(field, visit, step, nextRow, nextCol - 1);

            field[nextRow][nextCol] = ']';
            field[nextRow][nextCol - 1] = '[';
            field[row][col] = '.';
            field[row][col - 1] = '.';
        }
        else if (step == 1) {
            if (field[nextRow][nextCol] == '[')
                move_box(field, visit, step, nextRow, nextCol);
            field[nextRow][nextCol] = ']';
            field[nextRow][nextCol - 1] = '[';
            field[row][col-1] = '.';
        }
        else if (step == 3) {
            if (field[nextRow][nextCol-1] == ']')
                move_box(field, visit, step, nextRow, nextCol-1);
            field[nextRow][nextCol-1] = '[';
            field[row][col] = '.';
            field[row][col - 1] = ']';
        }
    }
}

void move(vector<vector<char>>& field, int step, int& row, int& col)
{
    const int nextRow = row + N[step][0];
    const int nextCol = col + N[step][1];
    int currRow = nextRow, currCol = nextCol;
    
    if (field[nextRow][nextCol] == '#' || 
        ((field[nextRow][nextCol] == '[' || field[nextRow][nextCol] == ']') && !check_move_box(field, step, nextRow, nextCol)) )
        return;

    const int n = isz(field);
    const int m = isz(field[0]);
    vvi visit(n, vi(m));
    move_box(field, visit, step, nextRow, nextCol);
    field[row][col] = '.';
    field[nextRow][nextCol] = '@';
    row = nextRow;
    col = nextCol;
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;
   
    std::vector<std::string> input;

    while (getline(fin, line)) {
        if (!isz(line))
            break;
        input.push_back(line);
    }
    const int n1 = isz(input);
    const int m1 = isz(input[0]);
    const int n = n1;
    const int m = 2 * m1;

    std::vector<std::vector<char>> field(n, vector<char>(m, '.'));

    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < m1; ++j)
        {
            if (input[i][j] == 'O')
            {
                field[i][2 * j] = '[';
                field[i][2 * j + 1] = ']';
            }
            else if (input[i][j] == '#')
            {
                field[i][2 * j] = field[i][2 * j + 1] = '#';
            }
            else if (input[i][j] == '@')
                field[i][2 * j] = '@';
        }

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
            if (field[i][j] == '[')
                answ += 100 * i + j;
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
