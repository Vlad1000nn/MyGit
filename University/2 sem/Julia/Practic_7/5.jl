# Проверяем граф на двудольность
using LightGraphs

function is_bipartite(g)
    colors = fill(0, nv(g))          # Создаем массив цветов для каждой вершины графа
    
    # Функция для проверки двудольности графа
    function dfs(v, color)
        colors[v] = color
        for w in neighbors(g, v)
            if colors[w] == color
                return false
            elseif colors[w] == 0 && !dfs(w, -color)
                return false
            end
        end
        return true
    end
    
    # Проверяем каждую вершину графа
    for v in vertices(g)
        if colors[v] == 0 && !dfs(v, 1)
            return false
        end
    end
    
    return true
end

g = SimpleGraph(4)
add_edge!(g, 1, 2)
add_edge!(g, 2, 3)
add_edge!(g, 3, 4)
add_edge!(g, 4, 1)

if is_bipartite(g)
    println("Граф является двудольным")
else
    println("Граф не является двудольным")
end