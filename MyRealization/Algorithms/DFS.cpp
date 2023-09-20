// Basic DFS with recursion
void dfs(vvi& graph, int v, int p)
{
    for (auto& it : graph[v])
        if (it != p) 
            dfs(graph, it, v);
}


// DFS with printing path to the vert
void dfs(vvi& graph,vi& path, int v, int p)
{
    path.push_back(v);
    for (auto& it : graph[v])
    {
        if (it != p) 
        {
            dfs(graph, path, it, v);
        }
    }
    cout << v << ":";
    for (auto& it : path) cout << it << ' ';
    cout << '\n';
    path.pop_back();
}


 //DFS with printing all subtrees
void dfs(vvi& graph, vi& tree, int v, int p)
{
    int begin = int(tree.size());
    tree.push_back(v);

    for (auto& it : graph[v])
    {
        if (it != p)
        {
            dfs(graph, tree, it, v);
        }
    }
    int end = int(tree.size());
    cout << "Поддерево вершины "<< v << ": { ";
    for (int i = begin; i < end;++i) cout << tree[i] << ' ';
    cout << "}\n";;
}


 //DFS with all sizes of subtrees
void dfs(vvi& graph, vi& treeSize, int v, int p)
{
    int n = graph.size();
    ++treeSize[v];
    for (auto& it : graph[v])
    {
        if (it != p)
        {
            dfs(graph, treeSize, it, v);
            treeSize[v] += treeSize[it];
        }
    }
}


 //DFS with all vert depths
void dfs(vvi& graph, vi& depth, int v, int p)
{
    depth[v] = depth[p] + 1;

    for (auto& it : graph[v])
        if (it != p)
            dfs(graph, depth, it, v);
}


// DFS with all subtree's heights
void dfs(vvi& graph, vi& height, int v, int p)
{
    for (auto& it : graph[v])
        if (it != p) {
            dfs(graph, height, it, v);
            height[v] = max(height[v], height[it] + 1);
        }
}

 //DFS with all parent vert
void dfs(vvi& graph, vi& parent, int v, int p)
{
    parent[v] = p;
    for (auto& it : graph[v])
        if (it != p) 
            dfs(graph, parent, it, v);
}

 //DFS with dist from 1 to all vert
void dfs(vector<vector<pair<int,int>>>& graph, vi& path, int v, int p)
{
    for (auto& it : graph[v])
        if (it.first != p) {
            path[it.first] = path[v] + it.second;
            dfs(graph, path, it.first, v);
        }
}


 //DFS with max and min num number during path to vert
void dfs(vvi& graph, set<int>& path, int v, int p)
{
    path.insert(v);
    for (auto& it : graph[v])
        if (it != p) 
            dfs(graph, path, it, v);
    assert(!path.empty());
    cout << "Максимальная вершина для " << v << ":" << *path.rbegin() << '\n';
    cout << "Минимальная вершина для " << v << ":" << *path.begin() << '\n';
    path.erase(v);
}

 //DFS with min and max edges during path to vert
void dfs(vector<vector<pair<int,int>>>& graph, set<int>& path, int v, int p)
{
    for (auto& it : graph[v]) {
        if (it.first != p) {
            path.insert(it.second);
            dfs(graph, path, it.first, v);
            path.erase(it.second);
        }
    }
    if (path.size()) {
        assert(!path.empty());
        cout << "Маскимальное ребро для " << v << ":" << *path.rbegin() << '\n';
        cout << "Минимальное ребро для " << v << ":" << *path.begin() << '\n';
    }
}