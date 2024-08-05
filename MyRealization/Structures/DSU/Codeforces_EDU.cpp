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

