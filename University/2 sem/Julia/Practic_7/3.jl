# Проверка графа на связность
using LightGraphs

# Создаем граф
g = SimpleGraph(4)
add_edge!(g, 1, 2)
add_edge!(g, 2, 3)
add_edge!(g, 3, 4)

# Провер граф на связность
is_connected(g)