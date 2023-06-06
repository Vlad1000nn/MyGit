# Определяем структуру Vector2D, представляющую двумерный вектор
struct Vector2D{T<:Real}
    x::T
    y::T
end

# Определяем структуру Segment2D, представляющую отрезок на плоскости
struct Segment2D{T<:Real}
    start::Vector2D{T}
    stop::Vector2D{T}
end