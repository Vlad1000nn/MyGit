# Проверка графа на связность

# Функция для обхода графа в глубину
function dfs(graph, start, visited)
    visited[start] = true        # Помечаем текущую вершину как посещенную
    for v in graph[start]        # Обходим все смежные вершины
        if !visited[v]           # Если вершина еще не была посещена, вызываем функцию dfs для нее
            dfs(graph, v, visited)
        end
    end
end

#Функция для проверки связности графа
function is_connected(graph)
    visited = falses(length(graph))     # Создаем массив для хранения информации о посещенных вершинах
    dfs(graph, 1, visited)              # Выбираем произвольную вершину и вызываем функцию dfs для нее
    return all(visited)                 # Если все вершины были посещены, то граф связный
end

# Создаем граф в виде массива списков смежности
graph = [[2, 3], [1, 3], [1, 2, 4], [3]]

# Проверяем граф на связность
is_connected(graph)