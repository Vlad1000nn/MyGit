# Лежат ли две точки по одну сторону от заданной кривой(F(x,y)=0)
function same_side_of_curve(p1::Vector2D, p2::Vector2D, F::Function)
    F(p1.x, p1.y) * F(p2.x, p2.y) > 0
end