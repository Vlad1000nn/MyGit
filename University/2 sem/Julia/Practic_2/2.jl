#n-й член Фибоначчи по формуле Бине
function formulaBine(n)
    root_5 = 5 ^ 0.5
    phi = ((1 + root_5) / 2)

    a = (myfastpow(phi,n) - (myfastpow((-phi), -n)) ) / root_5

    return round(a)
end

print(formulaBine(30))