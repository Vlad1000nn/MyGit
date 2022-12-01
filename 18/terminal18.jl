julia
using HorizonSideRobots
include("18.jl")
r=Robot("18.1.sit",animate=true)
main1!(r)
r=Robot("18.2.sit",animate=true)
main2!(r)