#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()


// Подсчёт плохих чисел на [start, last]
int64_t calc_bad(int64_t start, int64_t last) {

    int64_t ans = 0;

    const int len1 = isz(std::to_string(start));
    const int len2 = isz(std::to_string(last));
        
    int len = max(1, len1 / 2);
    int64_t number = std::stoll(std::to_string(start).substr(0, len));

    // Берём первую половинку которую можем и начинаем смотреть, входит ли такое число в диапазон
    std::string curr;
    int64_t curr_int;
    for(;;number++) {
        curr = std::to_string(number) + std::to_string(number);
        curr_int = std::stoll(curr);
        
        if(curr_int > last) break;
        if(curr_int < start) continue;
        
        ans += curr_int;
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
        auto f = std::find(s.begin() + l, s.end(), ','); // Ищем пару чисел
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