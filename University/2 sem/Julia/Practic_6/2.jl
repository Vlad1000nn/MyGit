# Проверка лежат ли две точки по одну сторону от прямой
function is_one(P::Vector2D{T}, Q::Vector2D{T}, s::Segment2D{T}) where T 
    l = s.B-s.A     # Направляющий вектор заданной прямой
    return sin(l, P-s.A)*sin(l,Q-s.A) > 0   # Если угол между (l,AP) и (l,BP) имеют один знак, значит точки с 1 стороны 
end