function perimetr!(robot)     #Ставим маркеры по периметру
    
    for side in(Nord,Ost,Sud,West)

        while (!isborder(robot,side))
            move!(robot,side)
            putmarker!(robot)
        end

    end

end

function perimetr2!(robot)     #Ставим маркеры по координатам
    
    for side in(Nord,Ost,Sud,West)
        while (!isborder(robot,side))
            move!(robot,side)
            x,y=get_coord(robot)
            check!(robot,abs(x),abs(y))
        end

    end

end

function check!(robot,x,y)          #Проверяем координаты
    if (x==0 || y==0)
        putmarker!(robot)
    end
end

function numsteps_along!(robot,side)::Int64
num_steps=0
while (!isborder(robot,side))
    move!(robot,side)
    num_steps+=1
end
return num_steps
end


function move_to_angle!(robot, angle=(Sud,West))            #Идём в угол
    back_path = NamedTuple{(:side,:num_steps),Tuple{HorizonSide, Int}}[]
    while !isborder(robot,angle[1]) || !isborder(robot, angle[2])
        push!( back_path, ( side = inverse(angle[1]), num_steps = numsteps_along!(robot, angle[1]) ) )
        push!(back_path, (side = inverse(angle[2]), num_steps = numsteps_along!(robot, angle[2])))  
    end
    return back_path
end

function HorizonSideRobots.move!(robot::CoordRobot, back_path::Vector{NamedTuple{(:side,:num_steps),Tuple{HorizonSide, Int}}})  #Домой
    back_path=reverse!(back_path)
    for next in back_path
        along!(robot, next.side, next.num_steps)
    end
end

function along!(robot,side,num_steps)
    for _i in 1:num_steps
        move!(robot,side)
    end
end


function main1!(robot)
back_path=move_to_angle!(robot)
perimetr!(robot)
HorizonSideRobots.move!(robot,back_path)
end

function main2!(robot)
back_path=move_to_angle!(robot)
perimetr2!(robot)
HorizonSideRobots.move!(robot,back_path)
end


inverse(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+2, 4))