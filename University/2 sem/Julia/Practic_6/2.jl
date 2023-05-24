# Лежат ли две точки по одну сторону от прямой
function same_side_of_line(p1::Vector2D, p2::Vector2D, line::Segment2D)
    parallel_vector = line.stop - line.start
    perpendicular_vector = Vector2D(parallel_vector.y, -parallel_vector.x)
    line_vector1 = p1 - line.start
    line_vector2 = p2 - line.start
    dot1 = dot(line_vector1, perpendicular_vector)
    dot2 = dot(line_vector2, perpendicular_vector)
    return dot1 * dot2 > 0
end