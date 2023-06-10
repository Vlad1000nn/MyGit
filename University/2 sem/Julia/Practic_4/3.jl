# Построение функций Бесселя
using Plots
function bessel(M::Integer, x::Real)
    sqrx = x*x
    a = 1/factorial(M)
    m = 1
    s = 0 
    
    while s + a != s
        s += a
        a = -a * sqrx /(m*(M+m)*4)
        m += 1
    end
    
    return s*(x/2)^M
end

values = 0:0.1:20
myPlot = plot()
for m in 0:5
	plot!(myPlot, values, bessel.(m, values))
end
display(myPlot)