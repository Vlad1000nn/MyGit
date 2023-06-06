#Нахождение приближённого решения уравнения cos(x) = x методом Ньютона
function newton(r::Function, a, epsilon, max_num)
    dx = -r(a) # вычисляем значение производной функции r в точке a
    k = 0
    while (abs(dx) > epsilon && k < max_num)
        a += dx     # вычисляем новое приближение
        k += 1
        dx = -r(a)  # вычисляем значение производной функции в новой точке
    end
    return a
end

# Производная
function r(x)
    return (cos(x) - x) / (-sin(x) - 1)
end

print(newton(r, 1, 0.01, 10))