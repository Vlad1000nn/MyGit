#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string line;

    std::vector<std::pair<int64_t, int64_t>> red_tails;


    while(getline(fin, line)) {
        int comma = line.find(',');

        int64_t col = std::stoll(line.substr(0, comma)); 
        int64_t row = std::stoll(line.substr(comma + 1, isz(line) - comma - 1));
        
        red_tails.emplace_back(row, col);
    }

    const int n = isz(red_tails);

    int64_t max_val = -1;

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int64_t height = std::abs(red_tails[i].first - red_tails[j].first) + 1;
            int64_t width  = std::abs(red_tails[i].second - red_tails[j].second) + 1; 
 
            int64_t curr_square = height * width;
            max_val = std::max(max_val, curr_square);
        }
    }

    fout << max_val;

    return 0;
}