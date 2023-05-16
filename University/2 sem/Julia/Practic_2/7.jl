#Нахождение приближённого решения уравнения cos(x) = x методом Ньютона
function newton(r::Function, a, epsilon, max_num)
    dx = -r(a)
    k = 0
    while (abs(dx) > epsilon && k < max_num)
        a += dx
        k += 1
        dx = -r(a)
    end
    return a
end

function r(x)
    return (cos(x) - x) / (-sin(x) - 1)
end

print(newton(r, 1, 0.01, 10))