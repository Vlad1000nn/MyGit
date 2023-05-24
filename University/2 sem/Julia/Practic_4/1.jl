# Тейлор для экспоненты
function taylor_exp(n::Int64, x)
    
    max_coef = 1/factorial(n)
   
    res = max_coef
    for i in 1:n
        max_coef = max_coef*n
        n = n-1
        res = res*x + max_coef
        
    end
    return res
end

println( taylor_exp(3, 5))