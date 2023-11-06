#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

#define isz(x) (int)(x).size();
#define all(x) (x).begin(), (x).end()

template<typename T>
using PriorityQueue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int INF = int(pow(2, 31) - 1);


// Basic DFS with matrix
void dfs(const vvi& graph, std::vector<bool>& visited, int v)
{
    const int n = (int)graph[v].size();
    visited[v] = true;
    std::cout << v << ' ';

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(graph, visited, i);
}

// Dijkstra from v to all other vertexes
vi Dijkstra(const vvi& graph, int v)
{
    const int n = isz(graph);
    vi dist(n, INF);
    vi visited(n);

    PriorityQueue<std::pair<int, int>> pq;
    pq.push({ 0,v });

    while (!pq.empty())
    {
        auto [currDist, curr] = pq.top();
        pq.pop();

        if (dist[curr] <= currDist) continue;

        dist[curr] = currDist;
        visited[curr] = 1;

        for (int i = 0; i < n; ++i)
        {
            if (i == curr || !graph[curr][i]) continue;
            pq.push({ currDist + graph[curr][i], i });
        }

    }

    return dist;
}

// Calculate all degrees and return average degree
long double degrees(const vvi& graph, vi& degrees)
{
    const int n = isz(graph);
    for (int i = 0; i < n; ++i)
        degrees[i] = std::count_if(all(graph[i]), [&](const auto x) { return x != 0; }) - (graph[i][i] != 0);

    return static_cast<long double>(std::accumulate(all(degrees), 0LL)) / isz(degrees);
}


using namespace std;


int main()
{
    vvi graph =
    {
        { 0, 6, 1, 9, 4, 4, 2, 3, 5 },
        { 6, 0, 2, 2, 4, 0, 5, 5, 0 },
        { 1, 2, 0, 1, 6, 9, 4, 6, 3 },
        { 9, 2, 1, 0, 1, 9, 9, 4, 3 },
        { 4, 4, 6, 1, 0, 2, 8, 3, 1 },
        { 4, 0, 9, 9, 2, 0, 9, 1, 2 },
        { 2, 5, 4, 9, 8, 9, 0, 8, 8 },
        { 3, 5, 6, 4, 3, 1, 8, 0, 9 },
        { 5, 0, 3, 3, 1, 2, 8, 9, 0 }
    };

    cout << "My graph:\n";

    for (auto& it : graph)
    {
        for (auto& it2 : it)
            cout << it2 << ' ';
        cout << '\n';
    }

    vector<bool> visited(9);
    cout << "dfs:\n";
    dfs(graph, visited, 0);
    cout << '\n';

    cout << "Distance from i to other vertexes:\n";

    for (int i = 0; i < 9; ++i)
    {
        vi curr = Dijkstra(graph, i);

        cout << i << ":\n";
        for (auto& it : curr)
            cout << it << ' ';
        cout << '\n';
    }


    vi degree(9);
    long double avg_degree = degrees(graph, degree);

    cout << "Vertexes degree's:\n";
    for (auto& it : degree)
        cout << it << ' ';

    cout << "\nAverage degree:" << avg_degree << '\n';

    return 0;
}