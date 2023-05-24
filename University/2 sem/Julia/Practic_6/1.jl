struct Vector2D{T<:Real}
    x::T
    y::T
end

struct Segment2D{T<:Real}
    start::Vector2D{T}
    stop::Vector2D{T}
end

"""
v1 = Vector2D{Float64}(1.0, 2.0)
v2 = Vector2D{Float64}(5.0, 2.0)
v3 = Vector2D{Float64}(3.0, 7.0)

p = Vector2D{Float64}(-3.0, 7.0)

pol = [v1, v2, v3]

println(point_inside_polygon(p, pol))
"""