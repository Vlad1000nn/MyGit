function cross!(robot)                      #Ставим крест

    putmarker!(robot)

    diagonal_along!(robot, Nord, Ost)
    diagonal_along!(robot, Nord, West)
    diagonal_along!(robot, Sud, Ost)
    diagonal_along!(robot, Sud, West)

end

function diagonal_along!(robot, side1, side2)    #Идём по диагонали и ставим маркеры

    num_steps1=0
    num_steps2=0

     while ( !isborder(robot,side1) && !isborder(robot,side2) )
        num_steps1+=try_move!(robot,side1)
        num_steps2+=try_move!(robot,side2)
        putmarker!(robot)
    end
    
                                                #Возвращаемся домой
    for _i in 1:num_steps1
        move!(robot,inverse(side1))
    end

    for _i in 1:num_steps2
        move!(robot,inverse(side2))
    end

end

function try_move!(robot,side)
    if (!isborder(robot,side))
        move!(robot,side)
        return 1
    else
        return 0
    end
end


function main!(robot)
cross!(robot)
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)