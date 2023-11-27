#include <bits/stdc++.h>

bool isSafe(int v, const std::vector<std::vector<int>>& graph, std::vector<int>& path, int pos) 
{
    // Проверка, существует ли ребро от последней добавленной вершины к v
    if (!graph[path[pos - 1]][v]) 
        return false;
    
    // Проверка, была ли вершина v уже добавлена в путь
    for (int i = 0; i < pos; i++) 
        if (path[i] == v) 
            return false;
    
    return true;
}

bool hamiltonianCycleUtil(std::vector<std::vector<int>>& graph, std::vector<int>& path, int pos) 
{
    // Проверка, если все вершины включены в гамильтонов цикл
    if (pos == (int)graph.size())
        return (graph[path[pos - 1]][path[0]] == 1 ? true : false);
        // Проверка, существует ли ребро от последней вершины к первой

    // Пробуем добавить вершины в гамильтонов цикл
    for (int v = 1; v < graph.size(); v++)
     {
        if (isSafe(v, graph, path, pos)) 
        {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1)) 
                return true;
            
            // Удаление вершины, если она не ведет к решению
            path[pos] = -1;
        }
    }

    return false;
}

std::vector<int> hamiltonianCycle(std::vector<std::vector<int>>& graph) 
{
    std::vector<int> path((int)graph.size(), -1);

    path[0] = 0;

    return (hamiltonianCycleUtil(graph, path ,1) ? path : std::vector<int>{});
}

int main()
 {
    std::vector<std::vector<int>> graph =
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

    std::vector<int> path = hamiltonianCycle(graph);

    for(auto& it : path)
        std::cout<<it<<' ';
        
    return 0;
}
