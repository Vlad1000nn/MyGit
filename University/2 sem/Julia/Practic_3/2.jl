#Решето Эратосфена
function resheto(n::Integer)
    prime_indexes = ones(Bool, n)
    prime_indexes[begin] = false
    i = 2
    prime_indexes[i^2:i:n] .= false 
    i=3
   
    while i <= n
        prime_indexes[i^2:2i:n] .= false
        i+=1
        while i <= n && prime_indexes[i] == false
            i+=1
        end

    end
    return findall(prime_indexes)
end