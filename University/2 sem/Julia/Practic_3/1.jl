#Является ли число n простым
function isPrime(n)

    for i in 2:sqrt(n)
        if n % i == 0
            return false
        end
    end
    return true
end