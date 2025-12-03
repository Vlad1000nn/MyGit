#include <bits/stdc++.h>

#define isz(x) (int)(x).size()

using namespace std;

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;

    int64_t ans = 0;

    while(std::getline(fin, s)) {

        auto max_d = std::max_element(s.begin(), s.end());
        char max_digit = *max_d;
        int max_digit_pos = max_d - s.begin();
        char next_digit;

        if(max_digit_pos == isz(s) - 1) {
            auto next_d = std::max_element(s.begin(), s.begin() + max_digit_pos);
            next_digit = max_digit;
            max_digit = *next_d;
        } else {
            next_digit = *std::max_element(s.begin() + max_digit_pos + 1, s.end());
        }
        ans += 10 * (max_digit - '0') + (next_digit) - '0';
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}
