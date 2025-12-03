#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()


// Подсчёт плохих чисел на [start, last]
int64_t calc_bad(int64_t start, int64_t last) {

    std::map<int64_t, int> used;

    int64_t ans = 0;

    const int len1 = isz(std::to_string(start));
    const int len2 = isz(std::to_string(last));

    std::string curr;
    int64_t curr_int, validate;
    for(int number = 1; ; ++number) {
        curr = std::to_string(number);

        for(int i = 1; i < 15; ++i) {
            curr += std::to_string(number);
            curr_int = std::stoll(curr);
            
            // Если итоговое число больше по длине last -> выходим
            if(isz(curr) > isz(std::to_string(last))) break;

            if(curr_int >= start && curr_int <= last && !used[curr_int]) {
                used[curr_int] = 1;
                ans += curr_int;
            } 
        }

        validate = std::stoll(std::to_string(number) + std::to_string(number));
        if(validate > last) break;
    }

    return ans;
}

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;
    getline(fin, s);

    int l = 0, r = 0;
    int defis;

    int64_t ans = 0, start, last;

    for(;;) {
        auto f = std::find(s.begin() + l, s.end(), ',');
        if(f == s.end()) break;

        r = f - s.begin();
        defis = std::find(s.begin() + l, s.begin() + r, '-') - s.begin();
        start = std::stoll(s.substr(l, defis - l));
        last = std::stoll(s.substr(defis + 1, r - defis - 1));

        ans += calc_bad(start, last);
        l = r + 1;
    }

    // + обработать последнюю пару
    {
        l = r + 1, r = isz(s);
        defis = std::find(s.begin() + l, s.begin() + r, '-') - s.begin();
        start = std::stoll(s.substr(l, defis - l));
        last = std::stoll(s.substr(defis + 1, r - defis - 1));
        ans += calc_bad(start, last);
    }

    cout << ans << '\n';
    fout << ans;

    fin.close();
    fout.close();

    return 0;
}