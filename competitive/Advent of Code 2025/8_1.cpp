#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

struct Point {
    int x,y,z;

    Point(int x_, int y_, int z_)
        : x(x_)
        , y(y_)
        , z(z_)
    { }

};

long double get_dist(const Point& p1, const Point& p2) 
{
    return sqrtl(1ll * (p1.x - p2.x) * (p1.x - p2.x) + 1ll * (p1.y - p2.y) * (p1.y - p2.y) + 1ll * (p1.z - p2.z) * (p1.z - p2.z));
}

class DSU {
private:

    vector<int> sz, parent;

    int getParent(int x)
    {
        return x == parent[x] ? x : parent[x] = getParent(parent[x]);
    }

public:

    DSU(int n)
     : sz(n, 1)
     , parent(n)
    { 
        iota(all(parent), 0);
    }


    void merge(int u, int v) {
        
        u = getParent(u);
        v = getParent(v);

        if(u == v) return;

        if(sz[u] < sz[v]) swap(u, v);

        sz[u] += sz[v];
        parent[v] = u;
        //return 1;
    }

    int64_t get()  {
        
        const int n = isz(sz);
        vector<int> ans(n, -1);
        set<int> used;

        for(int i = 0; i < n; ++i) {
            int curr = getParent(i);
            auto f = used.lower_bound(curr);
            if(f != used.end() && *f == curr) {
                ;
            } else {
                used.insert(curr);
                ans[i] = sz[curr];
            }
        }

        sort(all(ans));

        int pos = isz(ans) - 1;

        return 1ll * ans[pos] * ans[pos - 1] * ans[pos - 2];
    }

};



int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    vector<Point> points;

    std::string s;
    while(getline(fin, s)) {
        int pos1 = find(s.begin(), s.end(), ',') - s.begin();
        int pos2 = find(s.begin() + pos1 + 1, s.end(), ',') - s.begin();

        int num1 = stoi(s.substr(0, pos1));
        int num2 = stoi(s.substr(pos1 + 1, pos2 - pos1 - 1));
        int num3 = stoi(s.substr(pos2 + 1, s.size() - pos2 - 1));
        
        points.emplace_back(num1, num2, num3);
    }

    const int n = isz(points);
    vector<tuple<long double, int, int>> dist;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            long double curr = get_dist(points[i], points[j]);
            dist.emplace_back(curr, i, j);
        }
    }

    sort(all(dist));

    DSU dsu(n);

    int pos = 0;
    int q = 1000;
    while(q-- > 0) {
        dsu.merge(get<1>(dist[pos]), get<2>(dist[pos]));
        ++pos;
    }

    fout << dsu.get();

    fin.close();
    fout.close();

    return 0;
}

