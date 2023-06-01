# Проверяем граф на двудольность
using LightGraphs

# Создаем граф
g = SimpleGraph(4)
add_edge!(g, 1, 2)
add_edge!(g, 2, 3)
add_edge!(g, 3, 4)
add_edge!(g, 4, 1)

# Проверяем граф на двудольность
is_bipartite(g)