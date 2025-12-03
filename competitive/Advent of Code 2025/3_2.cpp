#include <bits/stdc++.h>

#define isz(x) (int)(x).size()

using namespace std;

constexpr int n = 12;

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;

    int64_t ans = 0;

    array<int, n> digits; 

    int left, right;

    while(std::getline(fin, s)) {

        left = -1;
        for(int i = isz(s) - 1, j = n - 1; j >= 0; --i, --j)
            digits[j] = i; // remember pos

        for(int i = 0; i < n; ++i) 
        {
            right = digits[i];
            if(right <= left) continue;

            auto new_max = std::max_element(s.begin() + left + 1, s.begin() + right);
            int new_max_val = *new_max - '0';
            int new_max_pos = new_max - s.begin();
            
            if(new_max_val >= s[right] - '0') 
                digits[i] = new_max_pos;
            
            left = digits[i];
        }
        for(int i = 0; i < n; ++i) {
            int pow10 = n - i - 1;
            ans += powl(10, pow10) * (s[digits[i]] - '0');
        }
        
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}
