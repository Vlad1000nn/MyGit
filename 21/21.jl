function moving_recursion!(robot,side)      #рекурсивно до стены,назад вдвойне,если не получится return false
    if (!isborder(robot,side))
         move!(robot, side)
         moving_recursion!(robot, side)
         for _i in 1:2
             if (!isborder(robot,inverse(side)))
                move!(robot, inverse(side))
             else
                 return false
             end
         end
     end
     return true
end

 
function main!(robot,side)
moving_recursion!(robot,side)
end

 inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)