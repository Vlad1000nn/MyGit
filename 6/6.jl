struct CoordRobot
    robot::Robot
    coord::Coordinates
end

CoordRobot(robot) = CoordRobot(robot, Coordinates()) 


mutable struct Coordinates
    x::Int
    y::Int
end
Coordinates() = Coordinates(0,0)

function HorizonSideRobots.move!(coord::Coordinates, side::HorizonSide)
    if side==Nord
        coord.y += 1
    elseif side==Sud
        coord.y -= 1
    elseif side==Ost
        coord.x += 1
    else #if side==West
        coord.x -= 1
    end
end

get_coord(coord::Coordinates) = (coord.x, coord.y)



function go_to_corner!(robot)
    while (!isborder(robot,Sud) || !isborder(robot,West))

        while (!isborder(robot,Sud))
            move!(robot,Sud)
        end

        while (!isborder(robot,West))
            move!(robot,West)
        end

    end
end

function go_to_home!(robot, )



end

function main1!(robot)

    go_to_corner!(robot)
    perimetr!(robot)
    go_to_home!(robot, coord_x, coord_y)
    

end