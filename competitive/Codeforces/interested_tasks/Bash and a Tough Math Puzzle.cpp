// https://codeforces.com/problemset/problem/914/D?locale=en

#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cstdint>


#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define debug(x) cout << #x << " = " << (x) << endl

using namespace std;


using vi = vector<int>;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

struct SD {

    vi a, s;
    const int gsize = 512;

    void buildG(int g) {
        const int start = gsize * g;
        const int end = min(isz(a), start + gsize);

        for (int i = start; i < end; ++i)
            s[g] = __gcd(s[g], a[i]);
    }


    void build(const vi& vec) {
        const int n = isz(vec);
        a = vec;
        //gsize = (int)ceil(sqrt(n) / 2.0);
        const int nG = n / gsize + 1;
        s.assign(nG, 0);
        for (int g = 0; g < nG; ++g)
            buildG(g);
    }

    void update(int index, int value) {
        a[index] = value;
        const int g = index / gsize;
        buildG(g);
    }

    int get(int left, int right, int x) {
        const int gl = left / gsize;
        const int gr = right / gsize;

        int cnt = 0;
        int curr = 0;
        if (gl == gr) {
            for (int i = left; cnt < 2 && i <= right; ++i) {
                cnt += (a[i] % x != 0);
            }
        }
        else {
            for (int i = left; cnt < 2 && i < (gl + 1) * gsize; ++i)
                cnt += (a[i] % x != 0);

            for (int i = gr * gsize; cnt < 2 && i <= right; ++i)
                cnt += (a[i] % x != 0);

            for (int g = gl + 1; cnt < 2 && g < gr; ++g) {
                if (s[g] % x != 0)
                {
                    for (int i = gsize * g; cnt < 2 && i < gsize * (g + 1); ++i)
                        cnt += (a[i] % x != 0);
                }
            }
        }

        return cnt < 2;
    }

};


void solve()
{
    int n; cin >> n;
    vi a(n); cin >> a;
    int q; cin >> q;
    SD sd;
    sd.build(a);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, x; cin >> l >> r >> x; --l; --r;
            cout << (sd.get(l, r, x) ? "YES\n" : "NO\n");
        }
        else if (type == 2) {
            int i, v; cin >> i >> v; --i;
            sd.update(i, v);
        }
    }
}


int32_t main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };


    while (t--) {
        solve();
    }

    return 0;
}
