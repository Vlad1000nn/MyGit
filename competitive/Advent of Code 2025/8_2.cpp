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
    int components;

    int getParent(int x)
    {
        return x == parent[x] ? x : parent[x] = getParent(parent[x]);
    }

public:

    DSU(int n)
     : sz(n, 1)
     , parent(n)
     , components(n)
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
        components -= 1;
        //return 1;
    }

    int get()  const {
        
        return components;
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
    while(true) {
        dsu.merge(get<1>(dist[pos]), get<2>(dist[pos]));
        if(dsu.get() == 1) {
            const int i = get<1>(dist[pos]);
            const int j = get<2>(dist[pos]);
            fout << 1ll * points[i].x * points[j].x;
            break;
        }
        ++pos;
    }

    fin.close();
    fout.close();

    return 0;
}

