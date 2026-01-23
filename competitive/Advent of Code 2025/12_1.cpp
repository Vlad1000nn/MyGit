#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()


std::vector<int> parse_line(const std::string& line) {

    int x = line.find('x');
    int colon = line.find(':');

    int r = std::stoi(line.substr(0, x));
    int c = std::stoi(line.substr(x + 1, colon - x - 1));

    std::vector<int> ans;
    ans.reserve(8);

    ans.push_back(r);
    ans.push_back(c);

    int start = colon + 2;
    for(int i = start; i < isz(line); ++i) {
        if(line[i] == ' ') {
            ans.push_back(std::stoi(line.substr(start, i - start)));
            start = i + 1;
        }
    }
    ans.push_back(std::stoi(line.substr(start, isz(line) - start)));

    return ans;
}


int main() {
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    
    std::vector<int> cnt(6);

    std::string line;
    while(std::getline(fin, line)) {
        if(line.find('x') != -1) break;
        if(line == "") continue;

        int i = line[0] - '0';
        for(int i = 0; i < 3; ++i) {
            std::getline(fin, line);
            cnt[i] += std::count(all(line), '#');
        }
    }

    std::vector<std::vector<int>> fields;
    fields.emplace_back(parse_line(line));

    while(getline(fin, line)) {
        fields.emplace_back(parse_line(line));
    }

    int ans = 0;

    int min_diff = 1000, max_diff = 0;
    std::set<int> diffs;

    for(auto& it : fields) {
        int have = (it[0] / 3) * (it[1] / 3);
        int need = it[2] + it[3] + it[4] + it[5] + it[6] + it[7];

        int need_cnt = 0;
        for(int i = 0; i < 6; ++i)
            need_cnt += cnt[i] * it[i + 2];

        int have_cnt = it[0] * it[1];

        if(need_cnt > have_cnt) {
            //cout << "need_cnt: " << need_cnt << ", have_cnt: " << have_cnt << endl;
            //min_diff = std::min(min_diff, std::abs(have_cnt - need_cnt));
            //max_diff = std::max(max_diff, std::abs(have_cnt - need_cnt));
            //diffs.insert(std::abs(have_cnt - need_cnt));
        }

        if(need > have) {
            cout << "need: " << need << ", have: " << have << endl;
            min_diff = std::min(min_diff, std::abs(have - need));
            max_diff = std::max(max_diff, std::abs(have - need));
            diffs.insert(std::abs(have - need));
        } else {
            ++ans;
        }
    }

    std::cout << "MIN: " << min_diff << endl;
    std::cout << "MAX: " << max_diff << endl;

    std::cout << "=== DIFFS ===" << endl;
    for(auto& it : diffs)
        cout << it << ' ';
    cout << endl;

    fout << ans;

    fin.close();
    fout.close();

    return 0;
}
