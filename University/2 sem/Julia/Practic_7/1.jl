# Генерация всех размещений с повторениями
function next_repit_plasement!(p::Vector{T}, n::T) where T<:Integer
    i = findlast(x->(x < n), p)
    isnothing(i) && (return nothing)
    p[i] += 1
    p[i+1:end] .= 1 
    return p
end