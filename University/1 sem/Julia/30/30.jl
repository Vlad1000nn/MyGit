function check_cell(x,y,a::Array)           #Проверка были ли в этой клетке
    if (a[x,y]==false)
        return true
    else
        return false
    end
end

function check_next_coords!(robot,side)         
    x,y=get_coord(robot)
    if (side==Nord)
        y+=1
    elseif (side==Sud)
        y-=1
    elseif (side==West)
        x-=1
    else
        x+=1
    end
    return x,y
end

function check_putmarker!(robot)
    x,y=get_coord(robot)
    if ( (x+y)%2==0)
        putmarker!(robot)
    end
end

function try_move!(robot,side,a::Array)
    x,y=check_next_coords!(robot,side)
    if ( !isborder(robot,side) )
        if (check_cell(x,y,a))
            move!(robot,side)
            check_putmarker!(robot)
            a[x,y]=true
            return true
        else
            return false
        end
    else
    return false
    end
end

function labirynth!(robot,a::Array)
    for side in (Nord,Ost,Sud,West)
        if ( !isborder(robot,side) && try_move!(robot,side,a) )
            labirynth!(robot,a)
            move!(robot,inverse(side))
        end
    end
end


function main!(robot)
a=zeros(Bool,15,15)
labirynth!(robot,a)
end

inverse(side::HorizonSide) = HorizonSide((Int(side) +2)% 4)