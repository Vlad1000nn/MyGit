function  shuttle!(stop_condition::Function, robot, side)       #Челнок обход стены
    n=0 
    start_side=side
while !stop_condition() 
 n += 1
 along_shuttle!(robot, right(side), n,()->!isborder(robot,start_side))
 side = inverse(side)
 if (stop_condition())
    break
 end
 along_shuttle!(robot,right(side),2n,()->!isborder(robot,start_side))
 side=inverse(side)
 if (stop_condition())
    break
 end
 along_shuttle!(robot,right(side),n,()->!isborder(robot,start_side))
end
if (n!=0)
    move!(robot,start_side)
    for _i in 1:n
        move!(robot,(right(side)))
    end
end
if (n==0)
    move!(robot,start_side)
end
end

function  along_shuttle!(robot, side, n,stop_condition::Function)        
for _i in 1:n
    if (!stop_condition())
    move!(robot,side)
    end
end
end


function spiral!(stop_condition::Function, robot)           #Спираль
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
    shuttle!(()->!isborder(robot,side),robot,side)
    end
end
end


function main!(robot)
spiral!(()->ismarker(robot),robot)
end

right(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+1, 4))
left(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)-1, 4))
inverse(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+2, 4))