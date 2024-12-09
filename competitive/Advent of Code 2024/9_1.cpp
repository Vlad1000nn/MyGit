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

    std::getline(fin, line);

    std::vector<int> empty_places;
    std::vector<std::pair<int, int>> digits_places;
    int current_place{0};
    int current_digit{};

    const int n = isz(line);
    for (int i = 0; i < n; ++i)
    {
        if (i % 2 == 0)
        {
            for (int j = i; j < i + line[i] - '0'; ++j) {
                digits_places.push_back({ current_place, current_digit });
                current_place++;
            }
            current_digit++;
        } else{
            for (int j = i; j < i + line[i] - '0'; ++j) {
                empty_places.push_back(current_place);
                current_place++;
            }
        }
    }
    const int m = isz(empty_places);
    const int q = isz(digits_places);
    for (int i = q - 1, j = 0; j < m; ++j, --i)
    {
        if (digits_places[i].first <= empty_places[j])
            break;
        digits_places[i].first = empty_places[j];
    }

    ll answ{};
    for (auto& it : digits_places)
        answ += it.first * it.second;
    std::cout << answ << '\n';
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
