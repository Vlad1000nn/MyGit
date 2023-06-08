# Проверка, лежит ли точка внутри многоугольника
function point_inside_polygon(p::Vector2D, poly::Array{Vector2D{T}, 1}) where T<:Real
    winding_number = 0
    num_vertices = length(poly)
    for i in 1:num_vertices
        edge_start = poly[i]
        edge_end = poly[mod(i, num_vertices) + 1]
        if edge_start.y != edge_end.y && min(edge_start.y, edge_end.y) < p.y <= max(edge_start.y, edge_end.y)
            x_intersection = edge_start.x + (p.y - edge_start.y) * (edge_end.x - edge_start.x) / (edge_end.y - edge_start.y)
            if p.x < x_intersection
                if edge_start.y < edge_end.y
                    winding_number += 1
                else
                    winding_number -= 1
                end
            end
        end
    end
    return winding_number != 0
end