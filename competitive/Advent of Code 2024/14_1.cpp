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


int calculate(const vector<string>& field, int startx, int endx, int starty, int endy)
{
    int answ{};
    for (int i = startx; i < endx; ++i)
        for (int j = starty; j < endy; ++j)
            answ += field[i][j] - '0';

    return answ;
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line;
    // поле 103 x 101
    const int n = 103;
    const int m = 101;

    vector<string> field(n, std::string(m, '0'));

    while (getline(fin, line))
    {
        int px, py, vx, vy;
        sscanf_s(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

        int endx = px + 100 * vx;
        while (endx < 0)
            endx += m;
        endx %= m;
        int endy = py + 100 * vy;
        while (endy < 0)
            endy += n;
        endy %= n;
        field[endy][endx]++;
    }

    ll answ{ 1 };

    // i: 0 -> n / 2, n/2 -> n
    // j: 0 -> m / 2, m/2 -> m

    cout << n / 2 << ' ' << m / 2 << '\n';
    cout << answ << '\n';
    answ *= calculate(field, 0, n / 2, 0, m / 2);
    cout << answ << '\n';
    answ *= calculate(field, n / 2 + 1, n, 0, m / 2);
    cout << answ << '\n';
    answ *= calculate(field, 0, n / 2, m / 2 + 1, m);
    cout << answ << '\n';
    answ *= calculate(field, n / 2 + 1, n, m / 2 + 1, m);

    cout << '\n' << answ << '\n';
  
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
