# Тейлор для экспоненты
function taylor_exp(n::Int64, x::T) where T
    a0 = one(T)
    res = a0
    for i in 1:n-1
        a0 *= x / (i+1)
        res += a0
    end
    return res

end

println( taylor_exp(20, 0.5))