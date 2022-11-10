function find_corner!(robot)    #Функция поиска угла

num_steps_Sud=0
num_steps_West=0

    while (!isborder(robot,Sud))    #Считаем шаги на юг
        move!(robot,Sud)
        num_steps_Sud+=1
    end

    while (!isborder(robot,West))   #Считаем шаги на Запад
        move!(robot,West)
        num_steps_West+=1
    end

 return num_steps_Sud, num_steps_West
end

function perimetr!(robot)     #Ставим маркеры по периметру
    
    for side in(Nord,Ost,Sud,West)

        while (!isborder(robot,side))
            move!(robot,side)
            putmarker!(robot)
        end

    end

end

function go_home!(robot, num_Steps1, num_steps2)   #Функция возвращения домой

    for _i in 1:num_steps2
        move!(robot,Ost)
    end

    for _i in 1:num_Steps1
        move!(robot,Nord)
    end

end

function main!(robot)
num_steps_Sud,num_steps_West=find_corner!(robot)
perimetr!(robot)
go_home!(robot, num_steps_Sud, num_steps_West)
end
