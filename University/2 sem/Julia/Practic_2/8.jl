struct Polynomials{k}
    coeffs::Vector{k}
    Polynomials{k}(coeffs::Vector{k})  where k = new(coeffs)
end

function Gorner(n::Int, a::T, t) where T
    i = 2
    while (i <= n)
        a[i] = a[i] + a[i-1]*t 
        i = i + 1;
    end
    pop!(a)
    return a
end

p(x) = 6*x^5 - 23*x^4 + 12*x^2 + 86

rp(x) = p(x) / (30*x^4 - 92*x^3 + 24*x)

println(newton(x->x+0,1,1))
println(Gorner(3, [1,2,1], -1))

"""
метод Горнера для вычисления значения многочлена x^2 + 2x + 1 в точке -1. 
"""