function wall_recursion!(robot,side)            #рекурсивно обойти стену
    if (isborder(robot,side))
        move!(robot,right(side))
        wall_recursion!(robot,side)
        move!(robot,inverse(right(side)))
    else
        move!(robot,side)
    end

end


function main!(robot,side)
wall_recursion!(robot,side)
end

right(side::HorizonSide) = HorizonSide((Int(side) +3)% 4)
inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)
