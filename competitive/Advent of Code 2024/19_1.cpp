#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    getline(fin, line);

    // Будем жадно пробовать все полотенца, которые начинаются с текущего цвета
    map<char, std::vector<std::string>> have;
    std::string curr = "";

    for (int i = 0; i < isz(line); ++i)
    {
        if (line[i] == ',') {
            have[curr[0]].push_back(curr);
            curr = "";
            ++i;
        }
        else {
            curr += line[i];
        }
    }
    have[curr[0]].push_back(curr);
   
    getline(fin, line);
    std::vector<std::string> need;
    while (getline(fin, line))
        need.push_back(line);

    // dp[i] - можем ли мы собрать подстроку длины i
    // обновлять ответ будем перебирая строки j < i

    int answ{};
    for (auto& it : need) {
        std::vector<std::string> substring(isz(it));
        for (int i = 0; i < isz(it); ++i)
            substring[i] = it.substr(0, i + 1);

        vi dp(isz(it));
        for (auto& polotence : have[it[0]])
            if (polotence == substring[isz(polotence) - 1])
                dp[isz(polotence) - 1] = 1;

        for (int i = 0; i < isz(it); ++i)
        {
            if (dp[i])
                continue;
            for (int j = 0; j < i; ++j)
            {
                if (!dp[j])
                    continue;
                std::string gg = substring[i].substr(j + 1);
                if (find(all(have[gg[0]]), gg) == have[gg[0]].end())
                    continue;
                dp[i] = 1;
                break;
            }
        }
        answ += dp[isz(it) - 1];
    }
    cout << answ << '\n';

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--)
        solve();

    return 0;
}
