#include <iostream>
#include <vector>
#include <algorithm>

// Функция для раскраски графа
std::vector<int> greedyColoring(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> result(n, -1);
    std::vector<bool> available(n, true);

    result[0]  = 0; // Назначаем первой вершине первый цвет

    for (int u = 1; u < n; u++) {
        // Сбрасываем доступные цвета
        std::fill(available.begin(), available.end(), true);

        // Проверяем цвета соседей и удаляем их из доступных
        for (int i = 0; i < n; i++) {
            if (graph[u][i] != 0 && result[i] != -1) {
                available[result[i]] = false;
            }
        }

        // Находим первый доступный цвет
        int cr;
        for (cr = 0; cr < n; cr++) {
            if (available[cr]) break;
        }

        result[u] = cr; // Назначаем вершине u цвет cr
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> graph1 = {
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

    std::vector<std::vector<int>> graph = {
    {0, 1, 1, 0, 0, 0}, 
    {1, 0, 1, 1, 1, 0}, 
    {1, 1, 0, 0, 1, 1}, 
    {0, 1, 0, 0, 1, 0}, 
    {0, 1, 1, 1, 0, 1}, 
    {0, 0, 1, 0, 1, 0}  
    };

    std::vector<int> colors = greedyColoring(graph);

    std::cout << "Vertex colors:" << std::endl;
    for (int i = 0; i < colors.size(); i++) {
        std::cout << "Vertex " << i + 1 << " --->  Color " << colors[i] << std::endl;
    }

    return 0;
}


//     1
//    / \
//   2---3
//  / \ / \
// 4---5---6