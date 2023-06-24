function jarvis!(points::AbstractArray{Vector2D{T}})::AbstractArray{Vector2D{T}} where T

    function next!(convex_shell2::AbstractVector{Int64}, points2::AbstractVector{Vector2D{T}}, ort_base::Vector2D{T})::Int64 where T
        cos_max = typemin(T)
        i_base = convex_shell2[end]
        resize!(convex_shell2, length(convex_shell2) + 1)
        for i in eachindex(points2)
            if points2[i] == points2[i_base] # тут не обязательно, что i == i_base
                continue
            end
            ort_i = points2[i] - points2[i_base] # - не нулевой вектор, задающий направление на очередную точку
            cos_i = cos(ort_base, ort_i)
            if cos_i > cos_max
                cos_max = cos_i
                convex_shell2[end] = i
            elseif cos_i == cos_max && dot(ort_i, ort_i) > dot(ort_base, ort_base) # на луче, содержащем сторону выпуклого многоугольника, может оказаться более двух точек заданного множества (надо выбрать самую дальнюю из них)
                convex_shell2[end] = i
            end
        end
        return convex_shell2[end]
    end

    @assert length(points) > 1
    ydata = [points[i].y for i in firstindex(points):lastindex(points)]
    i_start = findmin(ydata)
    convex_shell = [i_start[2]]
    ort_base = (x=oneunit(T), y=zero(T))

    while next!(convex_shell, points, ort_base) != i_start[2]
        ort_base = points[convex_shell[end]] - points[convex_shell[end-1]]
    end

	pop!(convex_shell)

    return points[convex_shell]
end

println("Алгоритм Джарвиса: ", jarvis!( [
		(x=0.0,y=0.0),
		(x=5.0,y=1.0),
		(x=4.0,y=3.0),
		(x=1.0,y=9.0),
		(x=-3.0,y=8.0),
		(x=-5.0,y=2.0),
		(x=-2.0,y=3.0),
	] ) )

# 8. Написать функцию, реализующую алгоритм Грехома построения выпуклой оболочки заданных точек плоскости.
function grekhom!(points::AbstractArray{Vector2D{T}})::AbstractArray{Vector2D{T}} where T
	ydata = (points[i].y for i in firstindex(points):lastindex(points))

    i_start = findmin(ydata)

    points[begin], points[i_start[2]] = points[i_start[2]], points[begin]

    sort!(@view(points[begin + 1:end]), by=(point -> angle(point, (x=oneunit(T), y=zero(T)))))

    push!(points, points[begin])

    convex = [firstindex(points), firstindex(points) + 1, firstindex(points) + 2]

    for i in firstindex(points)+3:lastindex(points)
        while length(convex) > 1 && sign(points[i] - points[convex[end-2]], points[convex[end-1]] - points[convex[end-2]]) < 0
            pop!(convex)
        end

        push!(convex, i)
    end

   	pop!(convex)

    return points[convex]
end


grekhom!(points::AbstractArray{Vector2D}) = jarvis!(points::AbstractArray{Vector2D})