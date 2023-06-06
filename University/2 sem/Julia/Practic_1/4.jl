#Решение Диофантово
function Diophantine_solve(a, b, c)
    d = gcd(a, b)
    if c % d != 0
        return nothing
    end
    
    a_d, x0, y0 = extended_gcd(a, b)
    x = x0 * (c ÷ d)
    y = y0 * (c ÷ d)
    
    return x, y
end

print(Diophantine_solve(14,29,3))