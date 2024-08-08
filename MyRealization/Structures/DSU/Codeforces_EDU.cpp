/* # Step 1 */

// Disjoint Sets Union

class DSU
{
private:

    std::vector<int> sz, parent;
    int u, v;

    void mergeDSU()
    {
        u = getParent(u);
        v = getParent(v);

        if (u == v)
            return;

        if (sz[u] < sz[v])
            std::swap(u, v);

        sz[u] += sz[v];
        parent[v] = u;
    }

    void getDSU()
    {
        parent[0] = getParent(u) == getParent(v);
    }
    

    int getParent(int u)
    {
        // Use this if u have cuts or smth related with edges
        // return (u == parent[u] ? u : getParent(parent[u]));

        return (u == parent[u] ? u : parent[u] = getParent(parent[u]));
    }


public:

    DSU(int n)
        : sz(n + 1, 1)
        , parent(n + 1)
    {
        std::iota(all(parent), 0);
    }

    void merge(int u, int v)
    {
        DSU::u = u;
        DSU::v = v;
        mergeDSU();
    }

    bool get(int u, int v)
    {
        DSU::u = u;
        DSU::v = v;
        getDSU();
        return parent[0];
    }


};


// Disjoint Sets Union 2

class DSU
{
private:

    std::vector<int> sz, el_min, el_max, parent;
    int u, v;

    void mergeDSU()
    {
        u = getParent(u);
        v = getParent(v);

        if (u == v)
            return;

        if (sz[u] < sz[v])
            std::swap(u, v);

        sz[u] += sz[v];
        parent[v] = u;
        setmin(el_min[u], el_min[v]);
        setmax(el_max[u], el_max[v]);
    }
    

    int getParent(int u)
    {
        // Use this if u have cuts or smth related with edges
        // return (u == parent[u] ? u : getParent(parent[u]));

        return (u == parent[u] ? u : parent[u] = getParent(parent[u]));
    }


public:

    DSU(int n)
        : sz(n + 1, 1)
        , parent(n + 1)
    {
        std::iota(all(parent), 0);
        el_min = el_max = parent;
    }

    void merge(int u, int v)
    {
        DSU::u = u;
        DSU::v = v;
        mergeDSU();
    }

    std::tuple<int,int,int> get(int u)
    {
        u = getParent(u);
        return { el_min[u],el_max[u],sz[u] };
    }


};

// Experience

class DSU
{
private:

    std::vector<int> exp, sz, parent, add;
    int u, v;


    void mergeDSU()
    {
        u = getParent(u);
        v = getParent(v);

        if (u == v)
            return;

        if (sz[u] < sz[v])
            std::swap(u, v);
        
        add[v] -= add[u];
        parent[v] = u;
        sz[u] += sz[v];
    }
    

    int getParent(int u)
    {
        // Use this if u have cuts or smth related with edges
        return (u == parent[u] ? u : getParent(parent[u]));

        //return (u == parent[u] ? u : parent[u] = getParent(parent[u]));
    }


public:


    DSU(int n)
        : sz(n + 1, 1)
        , add(n + 1)
        , exp(n + 1)
        , parent(n + 1)
    {
        std::iota(all(parent), 0);
    }


    void merge(int u, int v)
    {
        DSU::u = u;
        DSU::v = v;
        mergeDSU();
    }


    int get(int u)
    {
        int answ = 0;
        while (u != parent[u])
        {
            answ += add[u];
            u = parent[u];
        }
        answ += add[u];

        return answ;
    }


    void add_func(int index, int value)
    {
        add[getParent(index)] += value;
    }


};

// Cutting a graph
class DSU
{
private:

    std::vector<int> sz, parent;
    int u, v;


    void mergeDSU()
    {
        u = getParent(u);
        v = getParent(v);

        if (u == v)
            return;

        if (sz[u] < sz[v])
            std::swap(u, v);
        
        parent[v] = u;
        sz[u] += sz[v];
    }
    

    int getParent(int u)
    {
        // Use this if u have cuts or smth related with edges
        return (u == parent[u] ? u : getParent(parent[u]));

        //return (u == parent[u] ? u : parent[u] = getParent(parent[u]));
    }


public:


    DSU(int n)
        : sz(n + 1, 1)
        , parent(n + 1)
    {
        std::iota(all(parent), 0);
    }


    void merge(int u, int v)
    {
        DSU::u = u;
        DSU::v = v;
        mergeDSU();
    }


    bool get(int u, int v)
    {
        return getParent(u) == getParent(v);
    }


};


void solve()
{
    int n, m, k; cin >> n >> m >> k;
    while (m--) {
        int x, y; cin >> x >> y;
    }

    DSU dsu(n);
    const string CUT = "cut", ASK = "ask";
    vector<tuple<string, int, int>> requests;
    while (k--)
    {
        string type; cin >> type;
        int u, v; cin >> u >> v;
        requests.push_back({ type,u,v });
    }

    reverse(all(requests));

    vector<int> answ;
    for (auto& [type, u, v] : requests)
    {
        if (CUT == type)
        {
            dsu.merge(u, v);
        }
        else if (ASK == type)
        {
            answ.push_back(dsu.get(u, v));
        }
        else  throw 1;
    }
    reverse(all(answ));
    for (auto& it : answ)
        cout << (it ? "YES\n" : "NO\n");
}


// Monkeys


class DSU
{
private:
 
    vi sz, parent, time, left, right;
 
 
    int getParent(int u)
    {
        return (u == parent[u] ? u : getParent(parent[u]));
    }
 
public:
 
    DSU(const int n)
        : sz(n+1,1)
        , parent(n+1)
        , time(n+1, INF)
    {
        std::iota(all(parent), 0);
    }
 
    void merge(int x, int y, int currTime = INF)
    {
        if (x == y || x == -1 || y == -1)
            return;
 
        x = getParent(x);
        y = getParent(y);
 
        if (x == y)
            return;
 
        if (sz[x] < sz[y])
            std::swap(x, y);
 
        if (x == 1)
        {
            setmin(time[y], currTime);
        }
        else if (y == 1)
        {
            setmin(time[x], currTime);
            std::swap(x, y);
        }
        else {
            setmin(time[y], currTime);
        }
 
        parent[y] = x;
        sz[x] += sz[y];
 
    }
 
    void update(const int n)
    {
        for (int i = 1; i <= n; ++i)
        {
            int curr = i;
            while (curr != parent[curr])
            {
                setmin(time[i], time[curr]);
                curr = parent[curr];
            }
        }
    }
 
    const vi& get()   const
    {
        return time;
    }
 
};
 
 
void solve()
{
    int n, m; cin >> n >> m;
    DSU dsu(n);
 
    vi left(n + 1), right(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> left[i] >> right[i];
 
    vpii queries(m);
    for (auto& [first, second] : queries)
        cin >> first >> second;
    
    vi buffl = left, buffr = right;
 
    for (auto& [monkey, hand] : queries)
        hand == 1 ? left[monkey] = -1 : right[monkey] = -1;
 
    for (int i = 1; i <= n; ++i)
    {
        if (left[i] != -1)
            dsu.merge(i, left[i]);
        if (right[i] != -1)
            dsu.merge(i, right[i]);
    }
 
    reverse(all(queries));
 
    int currTime = m - 1;
    for (auto& [monkey, hand] : queries)
    {
        hand == 1 ? left[monkey] = buffl[monkey] : right[monkey] = buffr[monkey];
        dsu.merge(monkey, hand == 1 ? left[monkey] : right[monkey], currTime);
        --currTime;
    }
 
    dsu.update(n);
 
    vi answ = dsu.get();
    for (int i = 1; i <= n; ++i)
        std::cout << (answ[i] == INF ? -1 : answ[i]) << '\n';
 
}

/* Step 2 */

// People are leaving

class DSU
{
private:
 
    vi sz, parent;
 
 
    int getParent(int x)
    {
        return (x == parent[x] ? x : parent[x] = getParent(parent[x]));
    }
 
public:
 
    DSU(const int n)
        : sz(n+1,1)
        , parent(n+2)
    {
        std::iota(all(parent), 0);
    }
 
    void merge(int x)
    {
        int y = x + 1;
        x = getParent(x);
        y = getParent(y);
 
        parent[x] = y;
    }
 
    int get(int x)
    {
        return (getParent(x) == isz(parent) - 1 ? -1 : getParent(x));
    }
 
 
};
 
 
void solve()
{
    int n, m; cin >> n >> m;
    DSU dsu(n);
 
    const char MINUS = '-', GET = '?';
    while (m--)
    {
        char type; cin >> type;
        if (MINUS == type)
        {
            int x; cin >> x;
            dsu.merge(x);
        }
        else if (GET == type)
        {
            int x; cin >> x;
            std::cout << dsu.get(x) << '\n';
        }
        else throw 1;
    }
}


// Parking

class DSU
{
private:
 
    vi sz, parent;
 
 
    int getParent(int x)
    {
        return (x == parent[x] ? x : parent[x] = getParent(parent[x]));
    }
 
public:
 
    DSU(const int n)
        : sz(n+1,1)
        , parent(n+1)
    {
        std::iota(all(parent), 0);
    }
 
    void merge(int x, int y)
    {
        x = getParent(x);
        y = getParent(y);
        if (sz[x] < sz[y])
            std::swap(x, y);
 
        parent[y] = x;
        sz[x] += sz[y];
    }
 
    int add(int x)
    {
        x = getParent(x);
        int y = (x + 1 == isz(parent) ? getParent(1) : getParent(x + 1));
        parent[x] = y;
        sz[y] += sz[x];
 
        return x;
    }
 
};
 
 
void solve()
{
    int n; cin >> n;
    DSU dsu(n);
 
    while (n--)
    {
        int place; cin >> place;
        cout << dsu.add(place) << ' ';
    }
 
}

// Spannig Tree


class DSU
{
private:
 
    vi sz, parent;
 
 
    int getParent(int x)
    {
        return (x == parent[x] ? x : parent[x] = getParent(parent[x]));
    }
 
public:
 
    DSU(const int n)
        : sz(n+1,1)
        , parent(n+2)
    {
        std::iota(all(parent), 0);
    }
 
    void merge(int x, int y)
    {
        x = getParent(x);
        y = getParent(y);
        if (sz[x] < sz[y])
            std::swap(x, y);
 
        parent[y] = x;
        sz[x] += sz[y];
    }
 
    bool get(int x, int y)
    {
        return getParent(x) == getParent(y);
    }
 
 
};
 
struct Edge
{
    int w, u, v;
 
    bool operator<(const Edge& edge)
    {
        return this->w < edge.w;
    }
 
    friend std::istream& operator>>(std::istream& in, Edge& edge)
    {
        in >> edge.u >> edge.v >> edge.w;
        return in;
    }
};
 
void solve()
{
    int n, m; cin >> n >> m;
    DSU dsu(n);
    ll answ = 0;
 
    vector<Edge> edges(m);
    cin >> edges;
    
    sort(all(edges));
 
    for (auto& it : edges)
    {
        int u = it.u;
        int v = it.v;
        int w = it.w;
 
        if (!dsu.get(u, v)) {
            dsu.merge(u, v);
            answ += w;
        }
    }
 
 
    std::cout << answ;
 
}


// First Non-Bipartite Edge


class DSU
{
private:
 
    vi sz, parent, len;
 
 
    std::pair<int,int> getParent(int x)
    {
        if (x == parent[x])
            return { x,0 };
        std::pair<int, int> val = getParent(parent[x]);
        parent[x] = val.first;
        len[x] = (len[x] + val.second) % 2;
        return { parent[x], len[x] };
    }
 
public:
 
    DSU(const int n)
        : sz(n+1,1)
        , parent(n+1)
        , len(n+1)
    {
        std::iota(all(parent), 0);
    }
 
    bool merge(int x, int y)
    {
        std::pair<int, int> valX = getParent(x);
        std::pair<int, int> valY = getParent(y);
 
        if (valX.first == valY.first)
        {
            return valX.second != valY.second;
        }
 
        if (sz[valX.first] < sz[valY.first])
            std::swap(valX, valY);
 
 
        parent[valY.first] = valX.first;
        len[valY.first] = (1 + valX.second + valY.second) % 2;
        sz[valX.first] += sz[valY.first];
 
        return  1;
    }
 
   
 
};
 
 
void solve()
{
    int n, m; cin >> n >> m;
    DSU dsu(n);
    int answ{-1};
 
    for (int i = 1; i <= m; ++i)
    {
        int u, v; cin >> u >> v;
        if (!dsu.merge(u, v) && answ == -1)
        {
            answ = i;
        }
    }
 
    std::cout << answ;
 
 
 
}
