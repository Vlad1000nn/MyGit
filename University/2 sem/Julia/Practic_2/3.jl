#Считаем log(a,b) с погрешностью Eps

# log[1/a] x = - log[a] x
function log(a0, x, epsilon)
    a = a0; flag  = false
    if a < 1.0
        a = 1.0 / a
        flag = true
    end
    y = 0.0; z = x; t = 1.0;
    while abs(t) > epsilon || z < 1.0 / a || z > a
        # инвариант a^y * z^t == x
        if z > a
            z /= a
            y += t
        elseif  z < 1.0 / a
            z *= a
            y -= t
        else
            z *= z
            t /= 2.0
        end
    end

    return (flag) ? -y : y
end

print(log(0.2,15.67,1e-8))