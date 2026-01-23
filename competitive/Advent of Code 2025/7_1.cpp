#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s, curr;

    vector<string> field;

    getline(fin, s);
    int n,m;
    m = isz(s);
    curr = string(m + 2, '.');
    field.push_back(curr);
    field.push_back('.' + s + '.');

    while(getline(fin, s)) {
        field.push_back('.' + s + '.');
    }
    field.push_back(curr);
    n = isz(field) - 2;

    int si, sj;

    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= m; ++j)
            if(field[i][j] == 'S') {
                si = i;
                sj = j;
                break;
            }

    int ans = 0;
    queue<pair<int,int>> q;
    vector<vector<int>> visit(n + 2, vector<int>(m + 2));
    
    q.push(make_pair(si, sj));

    while(!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        if(row <= 0 || col <= 0 || row > n || col > m) continue;
        if(visit[row][col]) continue;
        visit[row][col] = 1;

        if(field[row + 1][col] == '^') {
            ++ans;
            field[row + 1][col + 1] = '|';
            field[row + 1][col - 1] = '|';
            q.push(make_pair(row + 1, col + 1));
            q.push(make_pair(row + 1, col - 1));
        } else {
            field[row+1][col] = '|';
            q.push(make_pair(row + 1, col));
        }
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}
