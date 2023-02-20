function try_move!(robot, side)
    check!(robot)
    if isborder(robot, side)
        return false
    else       
        move!(robot, side)
        check!(robot)
        return true
    end
end

function  go_to_corner!(robot,num_steps_Sud,num_steps_West)
    while (!isborder(robot,Sud))
        move!(robot,Sud)
        num_steps_Sud+=1
     end
     while (!isborder(robot,West))
        move!(robot,West)
        num_steps_West+=1
     end
end


function along!(robot, side)
    while (!isborder(robot,side))
        check!(robot)
        move!(robot, side)
        check!(robot)
    end
end

function snake!( robot, (move_side, next_row_side)::NTuple{2,HorizonSide} = (Nord, Ost)) 
    along!(robot, move_side)
    while try_move!(robot, next_row_side)
        move_side = inverse(move_side)
        along!(robot, move_side)
    end
end

function find_corner!(robot)        #Поиск угла
    num_steps_West=0
    num_steps_Sud=0
 while (!isborder(robot,Sud))
    move!(robot,Sud)
    num_steps_Sud+=1
 end
 while (!isborder(robot,West))
    move!(robot,West)
    num_steps_West+=1
 end
    return num_steps_Sud,num_steps_West
end

function go_to_home!(robot,num_steps_Sud,num_steps_West)        #Домой
    for _i in 1:num_steps_Sud
        move!(robot,Nord)
    end
    for _i in 1:num_steps_West
        move!(robot,Ost)
    end
end

function check!(robot)          #Проверка координат
    x,y=get_coord(robot)
    if ( ( ( abs(x+y) )%2 )==0 )
        putmarker!(robot)
    end
end


function main!(robot,(side1, side2)::NTuple{2,HorizonSide} = (Ost, Nord))
num_steps_Sud,num_steps_West=find_corner!(robot)
 snake!(robot,(side1,side2))
 go_to_corner!(robot,num_steps_Sud,num_steps_West)
 go_to_home!(robot,num_steps_Sud,num_steps_West)
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)