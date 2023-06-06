#Алгоритм быстрого возведения в степень
function myfastpow(a, n)
    k=n
    p=a
    t=1
 
    while k>0
        if iseven(k)
            k /= 2 
            p *= p
        else
            k -= 1 
            t *= p 
        end
    end
    return t
end

print(myfastpow(5,14))