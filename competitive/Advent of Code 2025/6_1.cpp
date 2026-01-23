#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;

    vector<vector<int64_t>> matr;
    vector<int64_t> nums;
    while(getline(fin, s)) {

        if(s[0] == '*' || s[0] == '+') break;
        
        nums.clear();
        std::stringstream ss(s);
        int64_t num;
        while(ss >> num)
          nums.push_back(num);

        matr.push_back(nums);        
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

    assert(isz(ops) == isz(matr[0]));

    vector<int64_t> ans(ops.begin(), ops.end());

    for(int i = 0; i < isz(matr); ++i) {
        for(int j = 0;j < isz(matr[i]); ++j) {
            if(ops[j] == 0)
                ans[j] += matr[i][j];
            else 
                ans[j] *= matr[i][j];
        }
    }

    fout << accumulate(all(ans), 0ll);

    fin.close();
    fout.close();

    return 0;
}
