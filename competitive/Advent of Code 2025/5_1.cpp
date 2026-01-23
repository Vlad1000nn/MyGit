#include <bits/stdc++.h>


#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

// Делаем вектор строк, мержим отрезки, делаем lbound по левой границе
vector<pair<int64_t, int64_t>> merge_segments(const vector<pair<int64_t, int64_t>>& segments)
{
    vector<pair<int64_t, int64_t>> ans;

    if(segments[1].first <= segments[0].second) {
        ans.emplace_back(segments[0].first, segments[1].second);
    } else {
        ans.emplace_back(segments[0].first, segments[0].second);
        ans.emplace_back(segments[1].first, segments[1].second);
    }

    for(int i = 2; i < isz(segments); ++i) {
        if(segments[i].first <= ans.back().second) {
            ans.back().second = max(ans.back().second, segments[i].second);
        } else {
            ans.emplace_back(segments[i].first, segments[i].second);
        }
    }

    return ans;
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    vector<pair<int64_t,int64_t>> segments;

    std::string s;
    while(getline(fin ,s)) {
        if(s == "") break;
        int defis_pos = s.find('-');
        int64_t l = stoll(s.substr(0, defis_pos));
        int64_t r = stoll(s.substr(defis_pos + 1, isz(s) - defis_pos - 1));
        segments.push_back(make_pair(l, r));
    }

    sort(all(segments));
    segments = merge_segments(segments);

    int ans = 0;
    while(getline(fin, s)) {
        int64_t curr = stoll(s);
        auto f = lower_bound(all(segments), make_pair(curr, curr), [&](const auto& x, const auto& y) {
            return x.second < y.second;
        });
        ans += (f != segments.end() && (*f).first <= curr);
    }

    fout << ans;

    fin.close();
    fout.close();

    return 0;
} 
