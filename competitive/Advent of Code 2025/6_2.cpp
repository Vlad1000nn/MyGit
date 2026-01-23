#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

int main() {
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;

    vector<vector<char>> matr;

    int max_len = 0;
    while(getline(fin, s)) {

        if(s[0] == '*' || s[0] == '+') break;
        vector<char> curr(all(s));
        matr.push_back(curr);
    }

    // 0 - +, 1 - *
    vector<int> ops;
    int idx = 0;
    while(idx < isz(s)) {
        if(s[idx] == '+')
            ops.push_back(0);
        else if(s[idx] == '*')
            ops.push_back(1);
        ++idx;
    }

    vector<int64_t> ans(all(ops));
    vector<string> nums(isz(matr[0])); // Собираем числа по столбцам

    for(int i = 0; i < isz(matr); ++i) {
        for(int j = 0; j < isz(matr[i]); ++j) {
            if(matr[i][j] != ' ') {
                nums[j] += matr[i][j];
            }
        }
    }

    int op_pos = 0;
    int j = 0;
    while(op_pos < isz(ops) && j < isz(matr[0])) {
        if(nums[j] == "") {
            op_pos++;
            ++j;
            continue;
        }

        if(ops[op_pos] == 0) {
            ans[op_pos] += stoll(nums[j]);
        } else {
            ans[op_pos] *= stoll(nums[j]);
        }
        ++j;
    }

    fout << accumulate(all(ans), 0ll);

    fin.close();
    fout.close();

    return 0;
}
