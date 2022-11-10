function move_recursion!(robot,side)   # рекурсивно до стены,вызов обхода и до симм. точки 
    if (!isborder(robot,side))
        move!(robot,side)
        move_recursion!(robot,side)
    else
        wall_recursion!(robot,side)
    end
    move!(robot,side)
end


function wall_recursion!(robot,side)            #Рекурсивно обход стены
    if (isborder(robot,side))
        move!(robot,right(side))
        wall_recursion!(robot,side)
        move!(robot,inverse(right(side)))
    else
        move!(robot,side)
    end

end


function main!(robot,side)
move_recursion!(robot,side)
move!(robot,inverse(side))
end

right(side::HorizonSide) = HorizonSide((Int(side) +3)% 4)
inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)
