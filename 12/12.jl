function snake!(robot)                  #идём с проверкой
    side=Ost
    k=0
    while ( !isborder(robot,Nord) || !isborder(robot,inverse(side)))
        k+=along_check!(robot,side)
        move!(robot,Nord)
        side=inverse(side)
    end
    return k
end

function check!(robot,side)             #функция проверки перегородки
    if (isborder(robot,Nord))
        while (isborder(robot,Nord))
            move!(robot,side)
        end
        return 1
    else
        return 0
    end
end

function along_check!(robot,side)           #функция along с проверкой
    k=0
    while (!isborder(robot,side))
        move!(robot,side)
        k+=check!(robot,side)
    end
    return k
end


function main!(robot)
num_borders=0
num_borders+=snake!(robot)
return num_borders
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)