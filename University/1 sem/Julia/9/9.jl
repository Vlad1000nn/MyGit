function find_corner!(robot)      #идём в угол и находим начальные координаты
    num_steps_Sud=0
    num_steps_West=0
    while (!isborder(robot,Sud))
        move!(robot,Sud)
        num_steps_Sud+=1
    end
    
    while (!isborder(robot,West))
        move!(robot,West)
        num_steps_West+=1
    end

    return num_steps_Sud, num_steps_West
end

function go_to_corner!(robot)           #Просто идём в угол
    while (!isborder(robot,Sud))
        move!(robot,Sud)
    end

    while (!isborder(robot,West))
        move!(robot,West)
    end
end


function go_to_home!(robot,num_steps_Sud,num_steps_West)        #Домой
    for _i in 1:num_steps_Sud
        move!(robot,Nord)
    end

    for _i in 1:num_steps_West
        move!(robot,Ost)
    end
end

function chess!(robot,coord_y,coord_x)      #проверка чётности
    if ( (coord_x+coord_y)%2==1 )
        move!(robot,Ost)
    end
end

function snake!(robot)              #Змейка
i=0  #счётчик чётности(каждые 2 шага маркер)
    side=Ost
    while ( !isborder(robot,Nord) || !isborder(robot,inverse(side)))
        i+=along!(robot,side)

         if (!isborder(robot,Nord))
             move!(robot,Nord)
             i+=1
         end


        if (i%2==0)
            putmarker!(robot)
        else
            move!(robot,inverse(side))
            i+=1
        end

        side=inverse(side)
    end


end

function along!(robot,side)         #Идём и ставим маркеры
    i=0
    while (!isborder(robot,side))
        if (i%2==0)
            putmarker!(robot)
        end
        move!(robot,side)
        i+=1
    end
    if (i%2==0)
        putmarker!(robot)
    end
    return i
end

function main!(robot)
num_steps_Sud, num_steps_West=find_corner!(robot)
chess!(robot,num_steps_Sud,num_steps_West)
snake!(robot)
go_to_corner!(robot)
go_to_home!(robot,num_steps_Sud,num_steps_West)
end

inverse(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+2, 4))