function  shuttle!(stop_condition::Function, robot, side)
    n=0 
    while !stop_condition() 
    n += 1
    along!(robot, side, n)
    side = inverse(side)
    end
end

function along!(robot, side, n)
    for _i in 1:n
    move!(robot,side)
    end
end

function main!(robot,side)
    if (isborder(robot,left(side)))
        shuttle!(()->!isborder(robot,left(side)),robot,side)
    elseif (isborder(robot,right(side)))
        shuttle!(()->!isborder(r,right(side)),robot,side)
    end
end

right(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+1, 4))
left(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)-1, 4))
inverse(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+2, 4))