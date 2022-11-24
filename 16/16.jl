function spiral!(stop_condition::Function, robot)
    n=0
    side=Nord
    while !stop_condition()
        n+=1
        for _i in 1:2
        along!(robot,side,n,stop_condition)
        side=left(side)
        end
    end
end

function along!(robot,side,n,stop_condition::Function)
    for _i in 1:n
        if !stop_condition()
        move!(robot,side)
        end
    end
end


function main!(robot)
spiral!(()->ismarker(robot),robot)
end

left(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)-1, 4))