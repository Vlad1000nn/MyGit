# Точка пересечения двух отрезков(nothing если не пересекаются)
function intersection(s1::Segment2D{T},s2::Segment2D{T}) where T
    A = [s1.B[2]-s1.A[2]  s1.A[1]-s1.B[1]
         s2.B[2]-s2.A[2]  s2.A[1]-s2.B[1]]

    b = [s1.A[2]*(s1.A[1]-s1.B[1]) + s1.A[1]*(s1.B[2]-s1.A[2])
         s2.A[2]*(s2.A[1]-s2.B[1]) + s2.A[1]*(s2.B[2]-s2.A[2])]

    x,y = A\b   # Случай с определителем матрицы отбросим
    # Если точка не принадлежит какому-либо сегменту, то нет ответа
    if isinner((;x, y), s1)==false || isinner((;x, y), s2)==false   
        return nothing
    end
    return (;x, y) #Vector2D{T}((x,y))
end

# Проверка на то, является ли точка внутренней для сегмента
isinner(P::Vector2D, s::Segment2D) = (s.A.x <= P.x <= s.B.x || s.A.x >= P.x >= s.B.x)  && (s.A.y <= P.y <= s.B.y || s.A.y >= P.y >= s.B.y)