#Обратный а в кольце M
function invmod(a::T, M::T) where T
    a, x, y = exceeded_gcd(a, M)
    if y == 0
        return nothing
    end
    return rem(y,M)
end