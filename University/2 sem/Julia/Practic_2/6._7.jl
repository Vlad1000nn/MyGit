# Корень функции методом Ньютона
function newton(r::Function, x, epsilon; num_max = 10)
    dx = -r(x)
    k=0
    while abs(dx) > epsilon && k <= num_max
        x += dx
        k += 1
    end
    k > num_max && @warn("Требуемая точность не достигнута")
    return x
end

f(x) = cos(x) - x   

r(x) = f(x)/(sin(x)+1)     #r(x) = f(x)/f'(x)

println(newton(f,1,1))