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

const int INF = int(1e9);
const ll INFL = ll(1e18);
const ull INFUL = ull(1e19);
////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


std::tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
    if (b == 0) {
        return std::make_tuple(a, 1, 0);
    }
    ll gcd, x1, y1;
    std::tie(gcd, x1, y1) = extended_gcd(b, a % b);
    ll x = y1;
    ll y = x1 - (a / b) * y1;
    return std::make_tuple(gcd, x, y);
}

std::pair<ll, ll> solve_diophantine(ll a, ll b, ll c) {
    ll gcd, x0, y0;
    std::tie(gcd, x0, y0) = extended_gcd(a, b);

    if (c % gcd != 0) {
        return make_pair(INFL, INFL);
    }

    ll x = x0 * (c / gcd);
    ll y = y0 * (c / gcd);
    return std::make_pair(x, y);
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    vector<vpll> vec = { {{},{},{}} };
    int ind{};

    const ll add = 10000000000000ll;

    while (getline(fin, line))
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

        vec.back()[ind] = make_pair(x + (ind == 2) * add, y + (ind == 2) * add);
        ++ind;
    }

    ll answ{};

    vector<vector<tuple<ll, ll, ll>>> good; // vector(sum, a, b)
    for (auto& vit : vec)
    {
        good.push_back({});
        // vit = vpii = (x, y), (x, y), (x,y)
        const ll ax = vit[0].first;
        const ll bx = vit[1].first;
        const ll ay = vit[0].second;
        const ll by = vit[1].second;
        const ll needx = vit[2].first;
        const ll needy = vit[2].second;

        const ll A = ax + ay;
        const ll B = bx + by;
        const ll Z = needx + needy;

        pair<ll, ll> solution = solve_diophantine(A, B, Z);
        if (solution == make_pair(INFL, INFL))
            continue;
       
        const ll& x = solution.first;
        const ll& y = solution.second;
        const ll help1 = B / gcd(A, B);
        const ll help2 = A / gcd(A, B);

        const ll n1 = (needx - bx * y - ax * x) / (help2 * bx - ax * help1);
        const ll n2 = (abs(y) / help2) + (abs(y) % help2 != 0);

        const ll x1 = x - n1 * help1;
        const ll y1 = y + n1 * help2;

        const ll x2 = x - n2 * help1;
        const ll y2 = y + n2 * help2;

        if (x1 >= 0 && y1 >= 0 && (x1 * ax + y1 * bx) == needx && (x1 * ay + y1 * by) == needy)
            good.back().emplace_back(3 * x1 + y1, x1, y1);
        if (x2 >= 0 && y2 >= 0 && (x2 * ax + y2 * bx) == needx && (x2 * ay + y2 * by) == needy)
            good.back().emplace_back(3 * x2 + y2, x2, y2);

        sort(all(good.back()));
        if (isz(good.back())) 
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
