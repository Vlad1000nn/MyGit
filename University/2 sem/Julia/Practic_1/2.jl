#Расширенный алгоритм Евклида с коэффициентами
function exceeded_gcd(a,b) 
    x, y = 1, 0
    _x, _y = y, x
    while b != 0
        r, k = (a % b)::INT, (a / b)::INT
        a, b = b, r
        x, _x = _x, x - k * _x
        y, _y = _y, y - k * _y
    end
    if a < 0
        a, x, y = -a, -x, -y
    end
    return a, x, y
end