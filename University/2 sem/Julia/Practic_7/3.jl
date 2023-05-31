# Проверка графа на связность
using LightGraphs
using MetaGraphs

function is_connected(graph)
    return isweaklyconnected(MetaGraph(graph))
end

# Создаем пример графа
graph = SimpleDiGraph(4)  # Создаем ориентированный граф с 4 вершинами
add_edge!(graph, 1, 2)  # Добавляем ребра
add_edge!(graph, 2, 3)
add_edge!(graph, 3, 4)

# Проверяем связность графа
if is_connected(graph)
    println("Граф связный")
else
    println("Граф несвязный")
end
