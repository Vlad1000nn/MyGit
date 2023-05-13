#Обратный а в кольце M
function invmod(a::T, M::T) where T
    a, x, y = exceeded_gcd(a, M)
    if x == 1
        return nothing
    end
    return rem(x,M)
end