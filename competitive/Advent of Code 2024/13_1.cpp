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

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for (auto& it : vec)
        out << it << ' ';

    return out;
}

////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    vector<vpii> vec = { {{},{},{}} };
    int ind{};

    while (getline(fin,line))
    {
        if (isz(line) == 0)
        {
            ind = 0;
            vec.push_back({ {},{},{} });
            continue;
        }
        char c;
        int x, y;
        if (line[0] == 'B')
            sscanf_s(line.c_str(), "Button %c: X+%d, Y+%d", &c, 1, &x, &y);
        else 
            sscanf_s(line.c_str(), "Prize: X=%d, Y=%d", &x, &y);
        
        vec.back()[ind] = make_pair(x, y);
        ++ind;
    }

    int answ{};

    // Сначала пробуем идеально попасть в X: Перебираем количество нажатий на кнопки и смотрим итог
    // Если попали и в Х и в У, сохраняем пары и сумму, потом просто сортим по сумме
    vector<vector<tuple<int, int, int>>> good; // vector(sum, a, b)
    for (auto& vit : vec)
    {
        good.push_back({});
        // vit = vpii = (x, y), (x, y), (x,y)
        const int ax = vit[0].first;
        const int bx = vit[1].first;
        const int ay = vit[0].second;
        const int by = vit[1].second;
        const int needx = vit[2].first;
        const int needy = vit[2].second;

        for (int i = 0; i <= 100; ++i)
        {
            for (int j = 0; j <= 100; ++j)
            {
                const int currx = ax * i + bx * j;
                const int curry = ay * i + by * j;
                if (currx == needx && curry == needy)
                    good.back().emplace_back(3 * i + j, i, j);
            }
        }
        sort(all(good.back()));
        if(isz(good.back()))
            answ += get<0>(good.back()[0]);
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
