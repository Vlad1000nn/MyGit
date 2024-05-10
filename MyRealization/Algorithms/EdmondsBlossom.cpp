#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <chrono>
#include <random>

class Timer
{
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<Clock> m_beg{ Clock::now() };
public:

    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};



class Blossom
{
private:

    // Adjacency list
    std::vector<std::vector<int>> adj;

    // Count of vertexes
    int V;

    // Queue of vertexes
    std::queue<int> q;

    // Father of the vertexes in tree
    std::vector<int> father;

    // Bases of blossoms
    std::vector<int> base;

    // Matching
    std::vector<int> match;

    // Vertexes in queue
    std::vector<bool> inq;

    // Vertexes in blossom
    std::vector<bool> inb;

    // Vertexes in path(LCA)
    std::vector<bool> inp;

    // Lowest Common Ancestor of u,v relative to the root
    int LCA(int root, int u, int v)
    {
        inp.assign(V, 0);

        while (true)
        {
            inp[u = base[u]] = true;

            if (u == root)
                break;

            u = father[match[u]];
        }
        
        while (!inp[v = base[v]])
            v = father[match[v]];

        return v;
    }

    // Mark vertexes that are in a blossom
    void mark_blossom(int lca, int u)
    {
        int v;

        while (base[u] != lca)
        {
            v = match[u];
            inb[base[u]] = inb[base[v]] = true;
            u = father[v];

            if (base[u] != lca)
                father[u] = v;
        }
    }

    // Contraction the blossom
    void blossom_contraction(int s, int u, int v)
    {
        int lca = LCA(s, u, v);

        inb.assign(V, 0);

        mark_blossom(lca, u);
        mark_blossom(lca, v);

        if (base[u] != lca)
            father[u] = v;

        if (base[v] != lca)
            father[v] = u;

        for (int u = 0; u < V; ++u)
            if (inb[base[u]])
            {
                base[u] = lca;

                if (!inq[u])
                {
                    inq[u] = true;
                    q.push(u);
                }
            }
    }

    // Trying to find augmenting path
    int find_augmenting_path(int s)
    {
        inq.assign(V, 0);
        father.assign(V, -1);

        std::iota(base.begin(), base.end(), 0);

        while (!q.empty())
            q.pop();

        inq[s] = true;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it)
            {
                int v = *it;

                if (base[u] != base[v] && match[u] != v)
                    if ((v == s) || (match[v] != -1 && father[match[v]] != -1))
                        blossom_contraction(s, u, v);
                    else if (father[v] == -1)
                    {
                        father[v] = u;

                        if (match[v] == -1)
                            return v;
                        else if (!inq[match[v]])
                        {
                            inq[match[v]] = true;
                            q.push(match[v]);
                        }
                    }
            }
        }

        return -1;
    }

    // Adding augment path
    int augment_path(int s, int t)
    {
        int u = t, v, w;

        while (u != -1)
        {
            v = father[u];
            w = match[v];

            match[v] = u;
            match[u] = v;

            u = w;
        }

        return (t != -1);
    }


public:

    // Basic constructor
    Blossom(int V = 0)
        : V(V)
        , base(V)
        , adj(V, std::vector<int>())
    { }

    // Constuctor with graph
    Blossom(const std::vector<std::vector<int>>& graph) : Blossom((int)graph.size())
    {
        Blossom::adj = graph;
    }

    // Build function with graph
    void build(const std::vector<std::vector<int>>& graph)
    {
        *this = Blossom{ graph };
    }

    // Start of the algo
    int find()
    {
        int ans = 0;

        match.assign(V, -1);

        for (int u = 0; u < V; ++u)
            if (match[u] == -1)
                ans += augment_path(u, find_augmenting_path(u));

        return ans;
    }

    // Printing the answer
    friend static std::ostream& operator<<(std::ostream& out, const Blossom& blossom)
    {
        for (int i = 0; i < blossom.V; ++i)
            if (i < blossom.match[i])
                out << i + 1 << ' ' << blossom.match[i] + 1 << '\n';

        return out;
    }
};


#include <random>
#include <fstream>

namespace Random
{
    std::mt19937 mt{ std::random_device{}() };

    int get(int min, int max)
    {
        std::uniform_int_distribution<> die{ min, max };
        return die(mt);
    }
}


int main()
{

    std::vector<std::vector<int>> graph0 =
    {
        { 1 },
        { 0, 2 },
        { 1, 3 },
        { 2, 4 },
        { 3, 5, 8 },
        { 4, 6 },
        { 5, 7 },
        { 6, 8 },
        { 4, 7 },
    };

    /*
    std::vector<std::vector<int>> graph1 =
    {
        { 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0, 1, 0 }
    };
    */

    std::vector<std::vector<int>> graph2 =
    {
        { 1 },
        { 0, 2 },
        { 1, 3, 4 },
        { 2, 3 }
    };

    /*
    std::vector<std::vector<int>> graph =
    {
        { 0, 1, 0, 0, 0 },
        { 1, 0, 1, 0, 0 },
        { 0, 1, 0, 1, 1 },
        { 0, 0, 1, 0, 1 },
        { 0, 0, 1, 1, 0 }
    };
    */

    std::vector<std::vector<int>> testgraph(100000);

    /*   testgraph =
       {
           { 1, 2, 3 },
           { 0, 2, 3 },
           { 0, 1, 3 },
           { 0, 1, 2, 4 },
           { 3 }
       };*/

    std::ofstream out("output.txt");

    
    for (int i = 0; i < 100000; ++i)
    {
        int u = Random::get(0, 99999);
        int v = Random::get(0, 99999);
        
        if (u == v) continue; 
        
        bool flag = 0;
        for(auto& it : testgraph[u])
            if (it == v)
                flag = 1;
        if (flag) continue;

        testgraph[u].push_back(v);
        testgraph[v].push_back(u);
        out << u << ' ' << v << '\n';
    }

    out.close();

    /*for (int i = 0; i < (int)testgraph.size(); ++i)
    {
        std::cout << i << ":";
        for (auto& it : testgraph[i])@
            std::cout << it << ' ';
        std::cout << '\n';
    }*/

    //Blossom blossom(graph0);
    Blossom blossom(testgraph);
   
    Timer t;
    int res = blossom.find();
    std::cout << std::fixed << t.elapsed() << "s\n";

    if (!res)
        std::cout << "No Matching found\n";
    else
        std::cout << "Total Matching = " << res << "\n" << blossom;

    std::ofstream match_out("matching.txt");

    match_out << blossom;

    return 0;
}