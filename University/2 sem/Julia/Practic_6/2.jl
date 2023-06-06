# Лежат ли две точки по одну сторону от прямой
function same_side_of_line(p1::Vector2D, p2::Vector2D, line::Segment2D)
    parallel_vector = line.stop - line.start                                 # Вычисляем вектор, параллельный прямой
    perpendicular_vector = Vector2D(parallel_vector.y, -parallel_vector.x)   # Вычисляем перпендикулярный вектор
    line_vector1 = p1 - line.start               # Вычисляем векторы, соединяющие точки p1 и p2 началом прямой
    line_vector2 = p2 - line.start
    dot1 = dot(line_vector1, perpendicular_vector)           # Вычисляем скалярное произведение этих векторов с перпдикулярным вектором
    dot2 = dot(line_vector2, perpendicular_vector)
     # Если произведение положительное, то точки лежат по одну сторону от прямой, и функция возвращает true, в противном случае - false
    return dot1 * dot2 > 0
end