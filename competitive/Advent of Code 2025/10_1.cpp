#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int get_bit(int x, int n)  {
    return (x >> n) & 1;
}


int main() {
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string line;
    std::vector<std::string> patterns;
    std::vector<std::vector<std::vector<int>>> buttons;
    std::vector<std::vector<int>> voltages;

    while(getline(fin, line)) {
        
        int sz = isz(line);
        std::vector<std::vector<int>> line_buttons;

        for(int i = 0; i < sz; ++i) {
            switch(line[i]) {
                case '[': {
                    std::string pattern;
                    ++i;
                    while(line[i] != ']') {
                        pattern.push_back(line[i] == '#' ? '1' : '0');
                        ++i;
                    }
                    patterns.emplace_back(pattern);
                    break;
                }
                case '(': {
                    ++i;
                    std::vector<int> nums;
                    std::string num_s;
                    while (line[i] != ')') {
                        if(line[i] == ',') {
                            nums.emplace_back(std::stoi(num_s));
                            num_s.clear();
                            ++i;
                            continue;
                        }
                        num_s += line[i];
                        ++i;
                    }
                    nums.emplace_back(std::stoi(num_s));
                    line_buttons.emplace_back(nums);
                    break;
                }
                case '{': {
                    ++i;
                    std::vector<int> nums;
                    std::string num_s;
                    while(line[i] != '}') {
                        if(line[i] == ',') {
                            nums.emplace_back(std::stoi(num_s));
                        
                            num_s.clear();
                            ++i;
                            continue;
                        }
                        num_s += line[i];
                        ++i;
                    }
                    nums.emplace_back(std::stoi(num_s));
                    
                    voltages.emplace_back(nums);
                    buttons.emplace_back(line_buttons);
                    break;
                }
                case ' ': {
                    break;
                }
                default: {
                    throw 1;
                }
            }
        }
    }

    int ans = 0;

    for(int i = 0; i < isz(patterns); ++i) {
        
        const int n = isz(buttons[i]);
        const std::string empty_pattern(isz(patterns[i]), '0');

        int min_val = n;
        
        for(int mask = 0; mask < (1 << n); ++mask) {
            std::string curr_pattern = empty_pattern;
            int bit_cnt = 0;
            for(int j = 0; j < n; ++j) {
                if(get_bit(mask, j)) {
                    for(auto& it : buttons[i][j]) {
                        curr_pattern[it] = '0' + '1' - curr_pattern[it];
                    }
                    ++bit_cnt;
                }
            }

            if(curr_pattern == patterns[i]) {
                min_val = std::min(min_val, bit_cnt);
            }
        }
        ans += min_val;
    }
    
    fout << ans;


    fin.close();
    fout.close();

    return 0;
}