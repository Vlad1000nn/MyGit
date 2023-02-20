function moving_recursion!(robot,side)      #Рекурсивно до стены,маркер и обратно
    if (isborder(robot, side))
        putmarker!(robot)
    else
        move!(robot, side)
        moving_recursion!(robot, side)
        move!(robot, inverse(side))
    end
end

function main!(robot,side)
moving_recursion!(robot,side)
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)
