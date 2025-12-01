#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()

constexpr int mod = 100;

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int curr = 50;
    int ans = 0;
    string s;
    while(getline(fin, s)) {
        char way = s[0];
        int cnt = stoi(s.substr(1, isz(s)));
        curr = (curr + ((way == 'L' ? -1 : 1) * cnt) + mod) % mod;
        ans += (curr == 0);
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}