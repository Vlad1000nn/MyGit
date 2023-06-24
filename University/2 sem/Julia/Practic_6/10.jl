# Площадь многоугольника методом треугольников
function area_triangle(poly::AbstractArray{Vector2D{T}})::T where T
    res = zero(T)

	# area = (yk + yk+1)(xk+1 − xk)/2
    for i in firstindex(poly)+1:lastindex(poly)-1
        res += xdot(poly[i] - (poly[1]), poly[i+1] - poly[1])
    end

    return res
end