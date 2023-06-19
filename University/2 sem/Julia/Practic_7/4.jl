# Генерация всех k-элементных подмножеств
function next_indicator!(indicator::AbstractVector{Bool}, k)
    @assert(k <= n)
    i = lastindex(indicator)
    while indicator[i] == 0
        i -= 1
    end
    m = 0 
    while i >= firstindex(indicator) && indicator[i] == 1 
        m += 1
        i -= 1
    end
    if i < firstindex(indicator)
        return nothing
    end
    indicator[i] = 1
    indicator[i + 1:end] .= 0
    indicator[lastindex(indicator) - m + 2:end] .= 1
    return indicator 
end