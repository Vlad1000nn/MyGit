# Вычисление экспоненты с машинной точностью
function machine_precision()
    eps = Float64(0.5)^52
    while (1.0 + eps) > 1.0
        eps /= 2.0
    end
    return eps
end

println(machine_precision())