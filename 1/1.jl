function cross!(robot)     #Делаем крест

for side in(Nord,Ost,Sud,West)
    along_and_back!(robot,side)
end

end

function along_and_back!(robot,side)   #Ставим маркеры до упора и идём назад

    num_steps=0

    while (!isborder(robot,side))
        move!(robot,side)
        putmarker!(robot)
        num_steps+=1
    end

    for _i in 1:num_steps
   move!(robot,inverse(side))
    end

end



function main!(robot)
putmarker!(robot)
cross!(robot)
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)