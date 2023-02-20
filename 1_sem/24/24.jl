function moving_recursion!(robot,side)              #До стены и наполовину назад рекурсивно
    if (!isborder(robot,side))
         move!(robot, side)
         if (!isborder(robot,side))
            move!(robot,side)
         end
         moving_recursion!(robot, side)
         move!(robot, inverse(side))
    end
end


function main!(robot,side)
moving_recursion!(robot,side)
end
 
inverse(side::HorizonSide) = HorizonSide((Int(side) +2)%4) 