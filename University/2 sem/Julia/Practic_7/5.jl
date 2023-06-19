# Генерация всех разбиений натурального числа
function next_split!(s ::AbstractVector{Int64}, k)
    k == 1 && return (nothing, 0)
    i = k-1 
    while i > 1 && s[i-1]>=s[i]
        i -= 1
    end
    s[i] += 1
    r = sum(@view(s[i+1:k]))
    k = i+r-1
    s[(i+1):(length(s)-k)] .= 1
    return s, k
end