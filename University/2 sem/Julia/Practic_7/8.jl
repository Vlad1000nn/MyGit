# Находим все компоненты связности графа

# Функция для обходарафа в глубину
function dfs(graph, start, visited, component)
    visited[start] = true             # Помечаем текущую вершину как посещенную
    push!(component, start)           # Добавляем текущую вершину в текущую компоненту связности
    for v in graph[start]             # Обходим все смежные вершины
        if !visited[v]                # Если вершина еще не была посещена, вызываем функцию dfs для нее
            dfs(graph, v, visited, component)
        end
    end
end

# Функция для нахождения компонент связности графа
function find_components(graph)
    visited = falses(length(graph))     # Создаем массив для хранения информации о посещенных вершинах
    components = []                     # Создаем массив для хранения компонент связности
    for v in 1:length(graph)            # Обходим все вершины графа
        if !visited[v]                  # Если вершина еще не была посещена, создаем новую компоненту связности и вызываем функцию dfs для нее
            component = []
            dfs(graph, v, visited, component)
            push!(components, component)          # Добавляем найденную компоненту связности в массив компонент
        end
    end
    return components         # Возвращаем массив компонент связности
end

# Создаем граф в виде массива списков смежности
graph = [[2, 3], [1, 3], [1, 2, 4], [3], [6], [5, 7], [6]]
components = find_components(graph)     # Находим компоненты связности графа
for component in components             # Выводим найденные компоненты связности на экран
    println(component)
end