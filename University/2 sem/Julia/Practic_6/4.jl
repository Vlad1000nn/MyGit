# Точка пересечения двух отрезков
function intersect_segments(s1::Segment2D, s2::Segment2D)
    x1, y1 = s1.start.x, s1.start.y
    x2, y2 = s1.stop.x, s1.stop.y
    x3, y3 = s2.start.x, s2.start.y
    x4, y4 = s2.stop.x, s2.stop.y
    A1 = (y2 - y1) / (x2 - x1)
    A2 = (y4 - y3) / (x4 - x3)
    b1 = y1 - A1*x1
    b2 = y3 - A3*x3

    if A1 == A2
        return false
    else
        x_intersect = (b1 - b2) / (A2 - A1)
        if x_intersect < max(min(x1, x2), min(x3, x4)) || x_intersect > min(max(x1, x2), (x3, x4))
            return false
        else
            return true
        end
    end
end