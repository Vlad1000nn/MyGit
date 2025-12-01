#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()

constexpr int mod = 100;

int calc_zeros(int l, int r) { 
    
    int x = ceil(l / 100.0);  // Первое число % mod == 0 
    int y = floor(r / 100.0); // Последнее число % mod == 0 
    
    return (x > y ? 0 : y - x + 1);
}

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int curr = 50, next;
    int ans = 0;
    int l, r;
    string s;
    while(getline(fin, s)) {
        char way = s[0];
        int cnt = stoi(s.substr(1, isz(s)));
        next = curr + ((way == 'L' ? -1 : 1) * cnt);
        l = (way == 'L' ? next : curr + 1);
        r = (way == 'L' ? curr - 1 : next);
        ans += calc_zeros(l ,r);
        curr = ((next % mod) + mod) % mod;
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}