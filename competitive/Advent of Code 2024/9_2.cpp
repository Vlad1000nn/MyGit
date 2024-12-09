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

    const int s = isz(line);

    std::vector<std::tuple<ll, ll, ll>> digits_places; 
    std::vector<std::tuple<ll, ll, ll>> empty_places;

    int current_place{};
    int current_number{};

    for (int i = 0; i < s; ++i)
    {
        if (i % 2 == 0) {
            digits_places.emplace_back(current_number, current_place, line[i] - '0');
            ++current_number;
        }
        else
            empty_places.emplace_back(-1, current_place, line[i] - '0');
       
        current_place += line[i] - '0';
    }


    const int n = isz(digits_places);
    const int m = isz(empty_places);
    for (int i = n - 1; i > 0; --i)
    {
        for (int j = 0; j < m; ++j)
        {
            ll diff = get<2>(digits_places[i]) - get<2>(empty_places[j]);
            if (diff <= 0 && get<1>(empty_places[j]) < get<1>(digits_places[i]))
            {
                get<1>(digits_places[i]) = get<1>(empty_places[j]);
                get<1>(empty_places[j]) += get<2>(digits_places[i]);
                get<2>(empty_places[j]) -= get<2>(digits_places[i]);
            }
        }
    }

    ll answ{};
    for (auto& [number, start, cnt] : digits_places)
        answ += number * ((start + start + cnt - 1) * cnt / 2);
    
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
