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

class SegmentTree {
private:

    int size, neutral;
    vi a, tree;
    int start, end, x, v_res = 0;
    int index, value;

    void clear(int v)
    {
        tree[v] = neutral;
    }

    void merge(int target, int source) {
        tree[target] = gcd(tree[target], tree[source]);
    }

    void update_vertex(int v, int vl, int vr)
    {
        clear(v);
        merge(v, vl);
        merge(v, vr);
    }

    void build_tree(int v, int left, int right) {
        if (left + 1 == right) {
            tree[v] = a[left];
        }
        else {
            int mid = (left + right) >> 1;
            int vl = (v << 1), vr = vl + 1;
            build_tree(vl, left, mid);
            build_tree(vr, mid, right);
            update_vertex(v, vl, vr);
        }
    }

    void get_tree(int v, int left, int right) {
        if (tree[v] % x == 0 || tree[v_res] > 1) return; // Либо всё ок в вершине, либо уже ответ No
        
        if (start <= left && end >= right) {
            if (left + 1 == right)
                ++tree[v_res];
            else {
                int mid = (left + right) >> 1;
                int vl = (v << 1), vr = vl + 1;
                get_tree(vl, left, mid);
                get_tree(vr, mid, right);
            }
        }
        else {
            int mid = (left + right) >> 1;
            int vl = (v << 1), vr = vl + 1;
            if (start < mid)
                get_tree(vl, left, mid);
            if (end > mid)
                get_tree(vr, mid, right);
        }
    }

    void update_tree(int v, int left, int right) {
        if (left + 1 == right) {
            tree[v] = value;
        }
        else {
            int mid = (left + right) >> 1;
            int vl = 2 * v, vr = vl + 1;
            if (index < mid)
                update_tree(vl, left, mid);
            else
                update_tree(vr, mid, right);
            update_vertex(v, vl, vr);
        }
    }


public:

    SegmentTree(int n, int neutral)
        : neutral(neutral)
        , size(n)
        , tree(size << 2, SegmentTree::neutral)
    {  }

    void build(const vi& vec) {
        a = vec;
        build_tree(1, 0, size);
    }

    int get(int start, int end, int x) {
        SegmentTree::start = start;
        SegmentTree::end = end + 1;
        SegmentTree::x = x;

        clear(v_res);
        get_tree(1, 0, size);

        return (tree[v_res] < 2);
    }


    void update(int index, int value) {
        SegmentTree::index = index;
        SegmentTree::value = value;
        update_tree(1, 0, size);
    }

};

void solve()
{
    int n; cin >> n;
    vi a(n); cin >> a;
    int q; cin >> q;
    SD sd;
    sd.build(a);
    //SegmentTree tree(n, 0);
    //tree.build(a);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, x; cin >> l >> r >> x; --l; --r;
            cout << (sd.get(l, r, x) ? "YES\n" : "NO\n");
            //cout << (tree.get(l, r, x) ? "YES\n" : "NO\n");
        }
        else if (type == 2) {
            int i, v; cin >> i >> v; --i;
            sd.update(i, v);
            //tree.update(i, v);
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
