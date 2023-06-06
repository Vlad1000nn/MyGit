#Нод чисел a и b
function gcd(a,b)
    while b != 0
        a, b = b, a % b 
    end
    return abs(a)
end

print(gcd(14,35))