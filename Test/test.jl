using HorizonSideRobots
function draw!(robot)
    num_Nord1, num_Ost1 = to_corner(robot)
    draw_perimeter!(robot)
    num_West1, num_Sud1 = to_first_place!(robot)
    draw_around!(robot)
    for _i in 1:num_Sud1
        move!(robot, Sud)
    end
    for _j in 1:num_West1
        move!(robot, West)
    end
    while num_Nord1 != 0
        move!(robot, Nord)
        num_Nord1 -= 1
    end
    while num_Ost1 != 0
        move!(robot, Ost)
        num_Ost1 -= 1
    end
    return num_Nord1, num_Ost1
end
function to_corner(robot)
    num_West = 0
    num_Sud = 0
    while !isborder(robot, West) || !isborder(robot, Sud)
        if isborder(robot, Sud)
            move!(robot, West)
            num_West += 1
        else
            move!(robot, Sud)
            num_Sud += 1
        end
    end
    return num_Sud, num_West
end
function draw_perimeter!(robot)
    for side in (Ost, Nord, West, Sud)
        while !isborder(robot, side)
            move!(robot, side)
            putmarker!(robot)
        end
    end
end
function to_first_place!(robot)
    side = Ost
    num_Nord = 0
    num_Horizental_move = 0
    while !isborder(robot, side)
        move!(robot, side)
        num_Horizental_move += 1
        putmarker!(robot)
        if isborder(robot, side) && !isborder(robot, Nord)
            move!(robot, Nord)
            num_Nord += 1
            putmarker!(robot)
            side = inverse(side)
        end
        if isborder(robot, Nord)
            break
        end
    end
    return num_Horizental_move - (num_Nord) * 12 + num_Nord, num_Nord
end

function draw_around!(robot)
    side = Ost
    while !isborder(robot, side) && isborder(robot, next(side))
        move!(robot, side)
        putmarker!(robot)
        if !isborder(robot, side) && !isborder(robot, next(side))
            side = next(side)
            move!(robot, side)
            putmarker!(robot)
            if side == Ost
                break
            end
        end
    end
end
inverse(side::HorizonSide) = HorizonSide((Int(side) +2) % 4)
next(side::HorizonSide) = HorizonSide((Int(side) +1) % 4)
# include("test.jl")
