# cos(x) = x бин поиском
function borisenco_bisection(f::Function, a, b, epsilon)
    x0 = a; x1 = b; 
    @assert f(x0) * f(x1) <= 0
    while abs(x0 - x1) > epsilon
        c = (x0 + x1) / 2   # Середина отрезка
        if f(x0) * f(c) < 0
            x1 = c
        else
            @assert f(c) * f(x1) <= 0
            x0 = c
        end
    end
    return (x0 + x1) / 2
end

function F(x)
    return cos(x) - x
end


print(borisenco_bisection(F,-1,3.5,1e-8))