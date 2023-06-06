#Считаем log(a,b)
function log2(n)
    logValue = -1
    while (n > 0)
        logValue = logValue + 1
        n = floor(n / 2)
    end
    return logValue
end

function log(a::Int64, b::Int64)
    return log2(b) / log2(a)
end

print(log(3,28))