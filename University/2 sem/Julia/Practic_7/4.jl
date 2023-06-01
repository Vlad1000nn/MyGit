# Находим все компоненты связности графа

using LightGraphs

# Создаем граф
g = SimpleGraph(5)
add_edge!(g, 1, 2)
add_edge!(g, 2, 3)
add_edge!(g, 4, 5)

# Используем функцию connected_components для поиска компонент связности
components = connected_components(g)

# Выводим результаты
println("Количество компонент связности: ", length(components))
for (i, component) in enumerate(components)
    println("Компонента связности $i: ", collect(component))
end