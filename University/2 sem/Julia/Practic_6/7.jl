# Проверка на выпуклость многоугольника
function isconvex(polygon::AbstractArray{Vector2D{T}})::Bool where T
	for i in firstindex(polygon):lastindex(polygon) # Проверяем поочерёдно углы(если все <180 выпуклый)
		if angle( polygon[i > firstindex(polygon) ? i - 1 : lastindex(polygon)] - polygon[i] , polygon[i % lastindex(polygon) + 1] - polygon[i] ) >= π
			return false
		end
	end
	return true
end