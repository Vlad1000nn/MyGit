julia
using HorizonSideRobots
include("26.jl")

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
    else 
        coord.x -= 1
    end
end

get_coord(coord::Coordinates) = (coord.x, coord.y)

struct CoordRobot
    robot::Robot
    coord::Coordinates
end

CoordRobot(robot) = CoordRobot(robot, Coordinates()) 

function HorizonSideRobots.move!(robot::CoordRobot, side)
    move!(robot.robot, side)
    move!(robot.coord, side)
end
HorizonSideRobots.isborder(robot::CoordRobot, side) = isborder(robot.robot, side)
HorizonSideRobots.putmarker!(robot::CoordRobot) = putmarker!(robot.robot)
HorizonSideRobots.ismarker(robot::CoordRobot) = ismarker(robot.robot)
HorizonSideRobots.temperature(robot::CoordRobot) = temperature(robot.robot)

get_coord(robot::CoordRobot) = get_coord(robot.coord)

function HorizonSideRobots.move!(robot::CoordRobot, side)
    move!(robot.robot, side)
    move!(robot.coord, side)
end
HorizonSideRobots.isborder(robot::CoordRobot, side) = isborder(robot.robot, side)
HorizonSideRobots.putmarker!(robot::CoordRobot) = putmarker!(robot.robot)
HorizonSideRobots.ismarker(robot::CoordRobot) = ismarker(robot.robot)
HorizonSideRobots.temperature(robot::CoordRobot) = temperature(robot.robot)

get_coord(robot::CoordRobot) = get_coord(robot.coord)

r=CoordRobot(Robot("26.sit",animate=true), Coordinates(1,1))
main!(r)