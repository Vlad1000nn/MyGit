# Проверка лежит ли точка внутри многоугольника
function isinside(point::Vector2D{T},polygon::AbstractArray{Vector2D{T}})::Bool where T
	sum = zero(Float64)

    # Если сумма углов 0 — снаружи. 2π — внутри
	for i in firstindex(polygon):lastindex(polygon)
		sum += angle( polygon[i] - point , polygon[i % lastindex(polygon) + 1] - point )
	end
	
    # Чтобы не было неточностей при сравнении сравним с π(если < то это 0, если больше то 2π)
	return abs(sum) > π
end