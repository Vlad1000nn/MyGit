#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
using namespace std;


int check_cell(const vector<vector<int>>& field, int row, int col)
{
    if(field[row][col] == 0) return 0;

    int cnt = 0;

    for(int dx = -1; dx <= 1; ++dx)
        for(int dy = -1; dy <= 1; ++ dy)
        {
            if(dx == 0 && dy == 0) continue;
            cnt += field[row + dx][col + dy] == 1;
        }

    return cnt < 4;
}


int main() {
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m;
    vector<vector<int>> field;

    std::string s;
    vector<int> curr;

    getline(fin, s);
    m = isz(s);
    curr.assign(m + 2, 0);
    field.push_back(curr);
    { // Обработка 1 строки
        for(int i = 0; i < isz(s); ++i) 
            if(s[i] == '@')
                curr[i + 1] = 1;
        field.push_back(curr);
    }

    while(getline(fin, s)) {
        curr.assign(m + 2, 0);
        
        for(int i = 0; i < isz(s); ++i) 
            if(s[i] == '@')
                curr[i + 1] = 1;
        field.push_back(curr);
    }

    curr.assign(m + 2, 0);
    field.push_back(curr);

    n = isz(field) - 2;


    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            ans += check_cell(field, i, j);
        }
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;

}
